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

/**
 * @brief Constructs the game engine with a default scene.
 * @param _deltaTime The amount of time that passes between update calls.
 */
FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime), physicsWorld(b2Vec2(0.0f, -10.0f / 10))
{
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

/**
 * @brief Adds a GameObject to the active scene.
 */
void FishModel::addGameObjectToScene(GameObject *toAdd)
{
	gameObjects.push_back(toAdd);
	gameObjectMap.emplace(toAdd->getName(), toAdd);

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
	GameObject* objectPtr = gameObjectMap.at(objectName);
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), objectPtr), gameObjects.end());
	gameObjectMap.erase(objectName);
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
	std::vector<ObjectRenderInformation> renderables;
	//Hitboxes collects the render data of all fixtures (only used when debug is true).
	std::vector<ObjectRenderInformation> hitBoxes;

	for(GameObject* gameObject : gameObjects)
	{
		//Update all GameObjects once per frame.
		gameObject->updateObject(deltaTime);

		ObjectRenderInformation renderInfo {gameObject->getLocation(), gameObject->getRotation(), gameObject->getScale(), gameObject->getGraphic()};
		renderables.push_back(renderInfo);

		//If we're debugging we want to render fixtures.
		if (debug)
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
				pos += fixtureTranslation;
				ObjectRenderInformation hitBoxRender{pos, toPhysics->getBody()->GetAngle() * 180 / M_PI, scale,
				                                     fixtureImage};
				hitBoxes.push_back(hitBoxRender);

					fixture = fixture->GetNext();
				}
			}
		}
	//Compiles all things to render together (on release, this loop will be ignored).
	for(ObjectRenderInformation& hitBox : hitBoxes)
	{
		renderables.push_back(hitBox);
	}

	emit renderGameObjects(renderables);
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
FishModel::~FishModel()
{
	for(GameObject* gameObject : gameObjects)
		delete gameObject;
}

/**
 * @brief Moves to the next task to complete.
 */
void FishModel::nextTask() {
	switch (currentScene) {
		case WATER_CHANGE:
			setScene(PREPARE_TANK);
			break;
		case FILTER_CHANGE:
			setScene(FEEDING);
			break;
		case FEEDING:
			setScene(ADD_FISH);
			break;
		case ADD_FISH:
			setScene(PREPARE_TANK);
			break;
		default:
			setScene(WATER_CHANGE);
			break;
	}
}

/**
 * @brief Sets the scene.
 * @param scene - The scene to be set.
 */
void FishModel::setScene(FishModel::SCENE_STATE scene) {
	currentScene = scene;
	//TODO(gcpease): Somehow update scene on UI.
}

FishModel::MouseToPhysicsChecker::MouseToPhysicsChecker(QPointF center, std::function<bool(QPointF, PhysicsGameObject*)> modelCallback) :
	center(center), callback(modelCallback){}

bool FishModel::MouseToPhysicsChecker::ReportFixture(b2Fixture* fixture)
{
	PhysicsGameObject* gameObject = (PhysicsGameObject*) fixture->GetBody()->GetUserData();
	return callback(center, gameObject);
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
	MouseToPhysicsChecker checker(position, callBack);

	//Define the area of the cursor.
	b2AABB areaToCheck;
	areaToCheck.upperBound.Set(position.x(), position.y());
	areaToCheck.lowerBound.Set(position.x(), position.y());

	physicsWorld.QueryAABB(&checker, areaToCheck);
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
		holdObject->onMouseHold(position);
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
		holdObject->onMouseRelease(position);
		holdObject = nullptr;
	}
}
