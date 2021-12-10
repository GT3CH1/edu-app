/**
 * Authors - Alex Richins, William Erignac
 * Last Modified - 12/3/2021
 *
 * The game engine of the fish training application.
 */

#include "fishmodel.h"
#include <QPoint>
#include "physicsgameobject.h"
#include "simpledropplet.h"
#include "fishtank.h"
#include <iostream>
#include <QPainter>
#include <QPen>
#include <cmath>
#include <queue>
#include <functional>

/**
 * @brief Constructs the game engine with a default scene.
 * @param _deltaTime The amount of time that passes between update calls.
 */
FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime), physicsWorld(b2Vec2(0.0f, -10.0f / 10))
{
	getGameObjectLambda = [=](std::string name) {return this->getGameObject(name);};
	addGameObjectLambda = [=](void* toAdd) {this->addGameObjectToScene((GameObject*)toAdd);};
	deleteGameObjectLambda = [=](std::string name) {this->deleteGameObject(name);};

	{
		PhysicsGameObject* dropplet = new SimpleDropplet(1, QPointF(0,0), 0, QPointF(1,1));
		addGameObjectToScene(dropplet);
	}

	{
		PhysicsGameObject* dropplet2 = new SimpleDropplet(2, QPointF(0.5,10), 0, QPointF(1,1));
		addGameObjectToScene(dropplet2);
	}

	{
		PhysicsGameObject* fishTank = new FishTank("FishTank", QPointF(0,0), 0, QPointF(10,5));
		addGameObjectToScene(fishTank);
	}
	setScene(PREPARE_TANK);
	// Create the quests linked list
	createQuests();
}

/**
 * @brief Creates the quests linked list
 */
void FishModel::createQuests()
{
	// Task 1
	FillBowl* fillBowl1;
	Wait* ageWater1;
	FillTank* fillTank1;

	quests.push_back(fillBowl1);
	quests.push_back(ageWater1);
	quests.push_back(fillTank1);

	// Task 2
	ChooseFish* chooseFish2;
	AddFish* addFish2;

	quests.push_back(chooseFish2);
	quests.push_back(addFish2);

	// Task 3
	AddFood* addFood3;

	quests.push_back(addFood3);

	// Task 4
	TurnOffWaterPump* turnOffWaterPump4;
	SwitchFilter* switchFilter4;
	TurnOnWaterPump* turnOnWaterPump4;

	quests.push_back(turnOffWaterPump4);
	quests.push_back(switchFilter4);
	quests.push_back(turnOnWaterPump4);

	// Task 5
	ChooseFish* chooseFish5;
	AddFish* addFish5;

	quests.push_back(chooseFish5);
	quests.push_back(addFish5);

	// Task 6
	FillBowl* fillBowl6;
	Wait* ageWater6;
	SiphonOldWater* siphon6;
	FillTank* fillTank6;

	quests.push_back(fillBowl6);
	quests.push_back(ageWater6);
	quests.push_back(siphon6);
	quests.push_back(fillTank6);
}

CallbackOptions FishModel::constructCallbackOptions()
{
	CallbackOptions options(getGameObjectLambda, addGameObjectLambda, deleteGameObjectLambda);
	return options;
}

/**
 * @brief Adds a GameObject to the active scene.
 */
void FishModel::addGameObjectToScene(GameObject *toAdd)
{
	gameObjects.push_back(toAdd);
	gameObjectMap.emplace(toAdd->getName(), toAdd);

	CallbackOptions options = constructCallbackOptions();
	toAdd->setCallbacks(options);

	auto* toAddPhysics = dynamic_cast<PhysicsGameObject*>(toAdd);
	if (toAddPhysics != nullptr)
		addBodyToWorld(toAddPhysics);
}

/**
 * @brief getGameObject
 * @param objectName, name of gameobject
 * @return gameobject pointer as requested
 */
GameObject* FishModel::getGameObject(std::string objectName)
{
	return gameObjectMap.at(objectName);
}

/**
 * @brief deleteGameObject
 * @param objectName, name of gameobject
 */
void FishModel::deleteGameObject(std::string objectName)
{
	GameObject *objectPtr = gameObjectMap.at(objectName);
	PhysicsGameObject* gameObject = dynamic_cast<PhysicsGameObject*>(objectPtr);
	if(gameObject)
		physicsWorld.DestroyBody(gameObject->getBody());
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), objectPtr), gameObjects.end());
	gameObjectMap.erase(objectName);

	delete objectPtr;
}

/**
 * @brief Adds a PhysicsGameObject to the active physics world.
 */
void FishModel::addBodyToWorld(PhysicsGameObject* objectToAdd)
{
	b2BodyDef bodyDef =  objectToAdd->getBodyDef();
	b2Body* body = physicsWorld.CreateBody(&bodyDef);
	objectToAdd->setBody(body);
}

/**
 * @brief Updates the active scene and sends all the objects
 * that need to be rendered at the end.
 */
void FishModel::updateGameObjects(){
	//Update the physics world.
	physicsWorld.Step(deltaTime, 6, 2);

	//Manage collisions from the physics world.
	b2Contact* contact =  physicsWorld.GetContactList();
	int contactCount = physicsWorld.GetContactCount();

	for(int i = 0; i < contactCount; i++)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		auto* gameObjectA = (PhysicsGameObject*) fixtureA->GetBody()->GetUserData();
		auto* gameObjectB = (PhysicsGameObject*) fixtureB->GetBody()->GetUserData();


		if(fixtureA->IsSensor())
			gameObjectA->onSensor(contact, true, gameObjectB);
		if(fixtureB->IsSensor())
			gameObjectB->onSensor(contact, false, gameObjectA);
		if(!(fixtureA->IsSensor() || fixtureB->IsSensor()))
		{
			gameObjectA->onCollision(contact, true, gameObjectB);
			gameObjectB->onCollision(contact, false, gameObjectA);
		}

		contact = contact->GetNext();
	}

	//Renderable collects the render data of all active objects.
	std::priority_queue<ObjectRenderInformation, std::vector<ObjectRenderInformation>, std::greater<ObjectRenderInformation>> renderables;
	//Hitboxes collects the render data of all fixtures (only used when debug is true).
	std::vector<ObjectRenderInformation> hitBoxes;

	for(GameObject* gameObject : gameObjects)
	{
		//Update all GameObjects once per frame.
		gameObject->updateObject(deltaTime);

		int hashCode = std::hash<std::string>()(gameObject->getName());

		ObjectRenderInformation renderInfo {gameObject->getLocation(), gameObject->getRotation(), gameObject->getScale(), gameObject->getGraphic(), gameObject->getLayer(), hashCode};
		renderables.push(renderInfo);
		auto* toPhysics = dynamic_cast<PhysicsGameObject*>(gameObject);

		//If we're debugging we want to render fixtures.
		if (debug && toPhysics)
		{
			//Fixtures can only be in PhysicsGameObjects.
			auto* toPhysics = dynamic_cast<PhysicsGameObject*>(gameObject);
			b2Fixture *fixture = toPhysics->getBody()->GetFixtureList();//Render all fixtures of the current object.
			while (fixture != nullptr) {
				b2Shape *shape = fixture->GetShape();

				QColor color = Qt::red;

				if (fixture->IsSensor())
					color = Qt::green;

				//fixtureTranslation is the vector between the center of the body
				//and the center of this fixture.
				QPointF fixtureTranslation;
				QPointF scale(1, 1);
				QImage fixtureImage = getColliderShape(shape, color, fixtureTranslation, scale);

				QPointF pos(toPhysics->getBody()->GetPosition().x, toPhysics->getBody()->GetPosition().y);
				float angle = toPhysics->getBody()->GetAngle();
				QPointF rotatedTranslation(fixtureTranslation.x()*cos(angle) - fixtureTranslation.y()*sin(angle),
										  fixtureTranslation.x()*sin(angle) + fixtureTranslation.y()*cos(angle));
				pos += rotatedTranslation;
				ObjectRenderInformation hitBoxRender{pos, angle* 180 / M_PI, scale,
				                                     fixtureImage};
				hitBoxes.push_back(hitBoxRender);

					fixture = fixture->GetNext();
			}
		}
	}
	std::vector<ObjectRenderInformation> allRenderables;

	//Compiles all things to render together (on release, this loop will be ignored).
	while(!renderables.empty())
	{
		allRenderables.push_back(renderables.top());
		renderables.pop();
	}

	for(ObjectRenderInformation hitBox : hitBoxes)
		allRenderables.push_back(hitBox);

	emit renderGameObjects(allRenderables);
}

/**
 * @brief Returns an image representing the given shape
 * (an empty image is sent if we don't know how to
 * show the given shape).
 * @param translation The vector between (0,0) (the center of the body) and the center of this shape.
 */
QImage FishModel::getColliderShape(b2Shape* shape, QColor penColor, QPointF& translation, QPointF& scale)
{
	QImage shapeImage;

	auto* circle = dynamic_cast<b2CircleShape*>(shape);
	auto* polygon = dynamic_cast<b2PolygonShape*>(shape);

	//If we have a circle, just draw a cirlce.
	if (circle != nullptr)
	{
		shapeImage = QImage((int)(shape->m_radius*2*20), (int)(shape->m_radius*2*20), QImage::Format::Format_RGBA64);
		shapeImage.fill(Qt::transparent);
		QPainter painter(&shapeImage);
		painter.setPen(penColor);
		painter.drawEllipse(0,0,shapeImage.width(), shapeImage.height());
		painter.drawLine(shapeImage.width()/2,shapeImage.height()/2, shapeImage.width(), shapeImage.height()/2);
		painter.end();
		translation = QPointF(circle->m_p.x,circle->m_p.y);
		scale =	QPointF(circle->m_radius * 2, circle->m_radius * 2);
	}
	else if (polygon != nullptr) //If we have a polygon...
	{
		b2Vec2 last = polygon->m_vertices[0];
		b2Vec2 current;

		//We need to get the bounds of the polygon to make an image...
		QRectF polygonBounds(QPointF(last.x, last.y), QPointF(last.x, last.y));
		//And collect the edges of the polygon.
		std::vector<QLineF> lines;

		for (int i = 1; i < polygon->m_count; i++)
		{
			current = polygon->m_vertices[i];
			if(current.x < polygonBounds.left())
				polygonBounds = QRectF(QPointF(current.x, polygonBounds.top()),QPointF(polygonBounds.right(), polygonBounds.bottom()));
			if(current.y < polygonBounds.top())
				polygonBounds = QRectF(QPointF(polygonBounds.left(), current.y),QPointF(polygonBounds.right(), polygonBounds.bottom()));
			if(current.x > polygonBounds.right())
				polygonBounds = QRectF(QPointF(polygonBounds.left(), polygonBounds.top()),QPointF(current.x, polygonBounds.bottom()));
			if(current.y > polygonBounds.bottom())
				polygonBounds = QRectF(QPointF(polygonBounds.left(), polygonBounds.top()),QPointF(polygonBounds.right(), current.y));

			lines.emplace_back(last.x,last.y,current.x,current.y);
			last = current;
		}

		last = polygon->m_vertices[0];
		lines.emplace_back(last.x, last.y, current.x, current.y);

		float imageScaledBy = 10;

		//Create the image with the polygon's bounds.
		qreal shapeScaleX = (polygonBounds.width()) * imageScaledBy + 1;
		qreal shapeScaleY = (polygonBounds.height()) * imageScaledBy + 1;
		shapeImage = QImage((int)shapeScaleX, (int)shapeScaleY, QImage::Format::Format_RGBA64);
		shapeImage.fill(Qt::transparent);
		QPainter painter(&shapeImage);
		painter.setPen(penColor);

		QPoint imageCenter(shapeImage.width()/2, shapeImage.height()/2);
		translation = polygonBounds.center();

		//Draw the edges of the polygon.
		for(QLineF line : lines)
		{
			painter.drawLine((line.p1() - translation)*imageScaledBy + imageCenter, (line.p2() - translation)*imageScaledBy + imageCenter);
		}

		painter.end();

		scale =	QPointF(polygonBounds.width(), polygonBounds.height());
	}

	return shapeImage;
}

/**
 * @brief Destroys this FishModel and all of its objects.
 */
FishModel::~FishModel() {
	removeAllGameObjects();
}

/**
 * @brief Moves to the next task to complete.
 */
void FishModel::nextTask() {
	switch (currentScene) {
		case PREPARE_TANK:
			setScene(ADD_FISH);
			break;
		//TODO: Figure out how to add more fish?
		case ADD_FISH:
			setScene(FEEDING);
			break;
		case FEEDING:
			setScene(FILTER_CHANGE);
			break;
		case FILTER_CHANGE:
			setScene(WATER_CHANGE);
		default:
			setScene(PREPARE_TANK);
			break;
	}
}

/**
 * @brief Creates the scene and adds all the game objects
 */
void FishModel::setScene(SCENE_STATE scene)
{
	removeAllGameObjects();
	currentScene = scene;
	auto tank = new Tank();
	auto background = new GameObject("background",QPointF(0,0),0,QPointF(20,14),QImage(":/res/background.png"),0);
	addGameObjectToScene(background);
	addGameObjectToScene(new Filter());
	addGameObjectToScene(new WaterPump());
	addGameObjectToScene(new Countertop(0));
	addGameObjectToScene(tank);
	switch (currentScene)
	{
		case WATER_CHANGE : {
			addGameObjectToScene(new Clock());
			addGameObjectToScene(new Bowl());
			addGameObjectToScene(new Fish());
			//TODO: spigot
			addGameObjectToScene(new Siphon());
			break;
		}
		case FILTER_CHANGE :
			addGameObjectToScene(new Fish());
			break;

		case FEEDING :
			addGameObjectToScene(new Fish());
			// food container
			// lots of food
			break;

		case ADD_FISH :
			addGameObjectToScene(new Fish());
			break;

		case PREPARE_TANK :
			// tank
			// bowl
			// clock
			// spigot
			break;

		default:
			// tank
			// game object water pump
			// game object filter
			break;
	}
}

bool FishModel::MouseToPhysicsChecker::ReportFixture(b2Fixture* fixture)
{
	PhysicsGameObject* gameObject = (PhysicsGameObject*) fixture->GetBody()->GetUserData();
	if (gameObject->getIsClickable())
	{
		if (greatestLayer == nullptr)
			greatestLayer = gameObject;
		else if (greatestLayer->getLayer() < gameObject->getLayer())
			greatestLayer = gameObject;
	}

	return true;
}

PhysicsGameObject* FishModel::MouseToPhysicsChecker::reportFrontmostObject()
{
	return greatestLayer;
}

/**
 * @brief Does the collision check for where the mouse is clicked.
 * @param position the position of the mouse.
 */
void FishModel::mouseClick(QPointF position)
{
	//Set up the callback that processes detected fixtures.
	b2Vec2 positionAsVector(position.x(), position.y());
	std::function<bool(QPointF, PhysicsGameObject*)> callBack = [&](QPointF center, PhysicsGameObject* gameObject){return this->mouseClickProcess(center, gameObject);};
	MouseToPhysicsChecker checker;

	//Define the area of the cursor.
	b2AABB areaToCheck;
	areaToCheck.upperBound.Set(position.x(), position.y());
	areaToCheck.lowerBound.Set(position.x(), position.y());

	physicsWorld.QueryAABB(&checker, areaToCheck);

	PhysicsGameObject* toClick = checker.reportFrontmostObject();

	if (toClick != nullptr)
		mouseClickProcess(position, toClick);
}

/**
 * @brief Triggers a clicked GameObject. Used in mouseClick.
 * @param position The position of the mouse.
 * @param gameObject A detected GameObject under the mouse.
 * @return Whether this object was clicked.
 */
bool FishModel::mouseClickProcess(QPointF position, PhysicsGameObject* gameObject)
{
	gameObject->onMouseClick(position);
	holdObject = gameObject;
	return true;
}

/**
 * @brief Triggers the object that is considered to be "held"
 * by the mouse.
 * @param position The position of the mouse.
 */
void FishModel::mouseHold(QPointF position)
{
	if (holdObject != nullptr)
	{
		if (holdObject->getIsClickable())
			holdObject->onMouseHold(position);
		else
			holdObject = nullptr;
	}
}

/**
 * @brief Triggers the object that is considered to be "held"
 * by the mouse.
 * @param position The position of the mouse.
 */
void FishModel::mouseRelease(QPointF position)
{
	if (holdObject != nullptr)
	{
		if (holdObject->getIsClickable())
			holdObject->onMouseRelease(position);
		holdObject = nullptr;
	}
}

/**
 * @brief Removes all game objects from the scene.
 */
void FishModel::removeAllGameObjects()
{
	auto objsToDel(gameObjectMap);
	for (auto gameObject: objsToDel)
		deleteGameObject(gameObject.first);
}
