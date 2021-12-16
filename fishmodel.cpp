/**
 * Authors - Alex Richins, William Erignac, Gavin Pease
 * Last Modified - 12/3/2021
 *
 * The game engine of the fish training application.
 */

#include "fishmodel.h"
#include <QPoint>
#include "physicsgameobject.h"
#include "physicgameobjectsfile.h"
#include <iostream>
#include <QPainter>
#include <QPen>
#include <cmath>
#include <functional>
#include <QTimer>
#include <queue>
#include <unordered_set>

/**
 * @brief Constructs the game engine with a default scene.
 * @param _deltaTime The amount of time that passes between update calls.
 */
FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime), physicsWorld(b2Vec2(0.0f, -10.0f / 10))
{
	getGameObjectLambda = [=](std::string name) {return this->getGameObject(name);};
	addGameObjectLambda = [=](void* toAdd) {this->addGameObjectToScene((GameObject*)toAdd, true);};
	deleteGameObjectLambda = [=](std::string name) {this->deleteGameObject(name);};
	addJointLambda = [=](b2JointDef* def) {return this->addJoint(def);};
	destroyJointLambda = [=](b2Joint* joint) {this->destroyJoint(joint);};
	getDeltaTimeLambda = [=]() {return this->getDeltaTime();};
	setScene(START);
}

/**
 * @brief Creates a set of methods that can be used by
 * GameObjects and Quests to modify the model.
 */
CallbackOptions FishModel::constructCallbackOptions()
{
	CallbackOptions options(getGameObjectLambda, addGameObjectLambda, deleteGameObjectLambda, addJointLambda, destroyJointLambda, getDeltaTimeLambda);
	return options;
}

/**
 * @brief Returns the time between frames (used in CallbackOptions)
 */
float FishModel::getDeltaTime()
{
	return deltaTime;
}

/**
 * @brief Adds a GameObject to the active scene.
 * @param runStart Whether this method is being run
 * at the start of a new scene (we want to wait until
 * all GameObjects have been instantiated before
 * running start() at the start of a scene).
 */
void FishModel::addGameObjectToScene(GameObject *toAdd, bool runStart)
{
	//All GameObjects are in the vector and map.
	gameObjects.push_back(toAdd);
	gameObjectMap.emplace(toAdd->getName(), toAdd);

	//GameObjects need ways to affect the model.
	CallbackOptions options = constructCallbackOptions();
	toAdd->setCallbacks(options);

	//PhysicsGameObjects need to have their bodies instantiated.
	auto* toAddPhysics = dynamic_cast<PhysicsGameObject*>(toAdd);
	if (toAddPhysics != nullptr)
		addBodyToWorld(toAddPhysics);

	if (runStart)
		toAdd->start();
}

/**
 * @brief getGameObject
 * @param objectName, name of gameobject
 * @return gameobject pointer as requested
 */
GameObject* FishModel::getGameObject(std::string objectName)
{
	if (gameObjectMap.count(objectName) < 1)
		return nullptr;
	return gameObjectMap.at(objectName);
}

/**
 * @brief deleteGameObject
 * @param objectName, name of gameobject
 */
void FishModel::deleteGameObject(std::string objectName)
{
	//If the GameObject is not in the map, dont delete it.
	if(gameObjectMap.count(objectName) == 0)
		return;
	GameObject *objectPtr = gameObjectMap.at(objectName);

	//If the GameObject is a PhysicsGameObject, its body needs to be removed from the world.
	PhysicsGameObject* gameObject = dynamic_cast<PhysicsGameObject*>(objectPtr);
	if(gameObject)
	{
		physicsWorld.DestroyBody(gameObject->getBody());
		if (gameObject == holdObject)
			holdObject = nullptr;
	}

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
 * @brief Adds a Joint to the active physics world. To
 * be used in CallbackOptions.
 */
b2Joint* FishModel::addJoint(b2JointDef *jointDefinition)
{
	return physicsWorld.CreateJoint(jointDefinition);
}

/**
 * @brief Removes a Joint from the active physics world.
 * To be used in CallbackOptions.
 */
void FishModel::destroyJoint(b2Joint *toDestory)
{
	physicsWorld.DestroyJoint(toDestory);
}

/**
 * @brief Collision entries are used to tell whether two
 * objects have already collided.
 */
FishModel::CollisionEntry::CollisionEntry(PhysicsGameObject* first, PhysicsGameObject* second)
	: CollisionEntry(first, second, false)
{}

/**
 * @brief Collision entries are used to tell whether two
 * objects have already collided.
 * @param forcePosition
 * If this is true, the object with the larger ascii name will
 * be put in the a slot (this is used when two objects have
 * collided normally).
 * If this is false, the "first" object will be put into the
 * a slot (this is used when one object has "sensed" another
 * through a sensor).
 *
 * These two forms of construction exist prevent duplicate calls
 * with the unordered sets of CollisionEntries; normal collisions
 * are always called on both objects, while sensor collisions can
 * be called on one object.
 */
FishModel::CollisionEntry::CollisionEntry(PhysicsGameObject* first, PhysicsGameObject* second, bool forcePosition)
{
	if (forcePosition)
	{
		a = first;
		b = second;
	}
	else
	{
		if (first->getName() > second->getName())
		{
			a = first;
			b = second;
		}
		else
		{
			a = second;
			b = first;
		}
	}
}

/**
 * @brief Used for unordered_set of CollisionEntries.
 */
size_t FishModel::CollisionEntry::hashCode() const
{
	return	std::hash<std::string>()(a->getName());
}

/**
 * @brief Used for unordered_set of CollisionEntries.
 */
bool FishModel::CollisionEntry::operator==(const CollisionEntry& other) const
{
	return a == other.a && b == other.b;
}

/**
 * @brief Updates the active scene and sends all the objects
 * that need to be rendered at the end.
 */
void FishModel::updateGameObjects(){
	//Update the physics world.
	physicsWorld.Step(deltaTime, 6, 6);

	//Manage collisions from the physics world.
	b2Contact* contact =  physicsWorld.GetContactList();
	int contactCount = physicsWorld.GetContactCount();

	/*
	 * Keep track of what collisions have already occurred.,
	 * and prevent duplicate collision calls.
	 */
	std::unordered_set<CollisionEntry> entries;
	std::unordered_set<CollisionEntry> sensorEntries;

	for(int i = 0; i < contactCount; i++)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		auto* gameObjectA = (PhysicsGameObject*) fixtureA->GetBody()->GetUserData();
		auto* gameObjectB = (PhysicsGameObject*) fixtureB->GetBody()->GetUserData();

		CollisionEntry entry(gameObjectA, gameObjectB);
		CollisionEntry sensorEntryA(gameObjectA, gameObjectB, true);
		CollisionEntry sensorEntryB(gameObjectB, gameObjectA, true);

		if(sensorEntries.count(sensorEntryA) == 0 && fixtureA->IsSensor())
		{
			gameObjectA->onSensor(contact, true, gameObjectB);
			sensorEntries.insert(sensorEntryA);
		}
		if(sensorEntries.count(sensorEntryB) == 0 && fixtureB->IsSensor())
		{
			gameObjectB->onSensor(contact, false, gameObjectA);
			sensorEntries.insert(sensorEntryB);
		}
		if(entries.count(entry) == 0 && !(fixtureA->IsSensor() || fixtureB->IsSensor()))
		{
			gameObjectA->onCollision(contact, true, gameObjectB);
			gameObjectB->onCollision(contact, false, gameObjectA);
			entries.insert(entry);
		}

		contact = contact->GetNext();
	}

	//Renderable collects the render data of all active objects.
	std::priority_queue<ObjectRenderInformation, std::vector<ObjectRenderInformation>, std::greater<ObjectRenderInformation>> renderables;
	//Hitboxes collects the render data of all fixtures (only used when debug is true).
	std::vector<ObjectRenderInformation> hitBoxes;

	/*
	 * We duplicate the list of objects to iterate over because
	 * some GameObjects instantiate new objects in their update methods.
	 */
	std::vector<GameObject*> toIterate (gameObjects);

	for(GameObject* gameObject : toIterate)
	{
		//Update all GameObjects once per frame.
		gameObject->updateObject(deltaTime);

		if (gameObject->getToRender())
		{
			int hashCode = std::hash<std::string>()(gameObject->getName());

			ObjectRenderInformation renderInfo {gameObject->getLocation(), gameObject->getRotation(), gameObject->getScale(), gameObject->getGraphic(), gameObject->getLayer(), hashCode};
			renderables.push(renderInfo);
		}

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

	/*
	 * Compiles all things to render together (on release, the hitbox loop will be ignored),
	 * in the order they should be rendered in.
	 */
	while(!renderables.empty())
	{
		allRenderables.push_back(renderables.top());
		renderables.pop();
	}

	for(ObjectRenderInformation hitBox : hitBoxes)
		allRenderables.push_back(hitBox);

	//Update the quests to see if the current quest requirements have been satisfied.
	if(quests.front() != nullptr && quests.size() > 0)
		quests.front()->listener(constructCallbackOptions());

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
	if (fishInTank)
		delete fishInTank;
}

/**
 * @brief Moves to the next task to complete.
 */
void FishModel::nextTask() {
	switch (currentScene) {
		case START:
			setScene(PREPARE_TANK);
			break;
		case PREPARE_TANK:
			setScene(ADD_FISH);
			break;
		case ADD_FISH:
			setScene(FEEDING);
			break;
		case FEEDING:
			setScene(END);
			break;
		case END:
			setScene(START);
			break;
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
	holdObject = nullptr;
	removeAllGameObjects();
	currentScene = scene;

	auto tank = new Tank();
	GameObject* background;

	//If we are in the game (not a menu) there are a list of objects that are always there.
	if (currentScene != START && currentScene != END)
	{
		background = new GameObject("background",QPointF(0,0),0,QPointF(26,15),QImage(":/res/background.png"),-1);
		GameObject* sky = new GameObject("sky", QPointF(5.3, -1), 180, QPointF(13,13), QImage(":/res/sky_wheel.png"), -2);
		addGameObjectToScene(sky, false);
		addGameObjectToScene(new Countertop(QPointF(0,-7), QPointF(20,4.7)), false);
		addGameObjectToScene(new Wall("left wall", QPointF(-22.5, 0),QPointF(25, 14.5)), false);
		addGameObjectToScene(new Wall("right wall", QPointF(22.5, 0),QPointF(25, 14.5)), false);
		addGameObjectToScene(new Wall("ceiling", QPointF(0, 19.5),QPointF(25, 25)), false);
		addGameObjectToScene(new Filter(), false);
		addGameObjectToScene(new WaterPump(), false);
		addGameObjectToScene(tank, false);
	}
	else
	{
		background = new GameObject("background",QPointF(0,0),0,QPointF(20.7,14.5),QImage(":/res/start_background.png"),-1);
	}

	addGameObjectToScene(background, false);

	//Remove all quests so that the quests for this scene can be added.
	while(!quests.empty()) {
		delete quests.front();
		quests.pop();
	}

	switch (currentScene)
	{
		case START:
		{
			addGameObjectToScene(new StartButton(), false);
			quests.push(new Start());
			break;
		}
		case PREPARE_TANK :
		{
			addGameObjectToScene(new Clock(), false);
			addGameObjectToScene(new Bowl(QPointF(-5, -3)), false);
			addGameObjectToScene(new Spigot(QPointF(-5, 2)), false);
			quests.push(new FillBowl());
			quests.push(new Wait());
			quests.push(new FillTank());
			break;
		}
		case ADD_FISH :
		{
			auto pleco = new Fish();
			pleco->setFishType(Fish::PLECO);
			pleco->setName("pleco");
			pleco->setLocation(QPointF(-8, -3.5));

			auto moorish = new Fish();
			moorish->setFishType(Fish::SIMPLE);
			moorish->setName("moorish");
			moorish->setLocation(QPointF(-5.5, -3.5));

			auto goldfish = new Fish();
			goldfish->setFishType(Fish::GOLDFISH);
			goldfish->setName("goldfish");
			goldfish->setLocation(QPointF(-3, -3.5));
			tank->setWaterLevel(100);
			addGameObjectToScene(pleco, false);
			addGameObjectToScene(moorish, false);
			addGameObjectToScene(goldfish, false);
			addGameObjectToScene(new Clock(), false);

			quests.push(new ChooseFish());
			quests.push(new AddFish());
			quests.push(new Wait());
			auto removeBagQuest = new RemoveFishFromBag();
			quests.push(removeBagQuest);
			connect((RemoveFishFromBag *) removeBagQuest, &RemoveFishFromBag::fishRemovedFromBag, this,
			        &FishModel::addFishToTank);
			break;
		}
		case FEEDING :
		{
			fishInTank->setLocation(QPointF(5, -2));
			addGameObjectToScene(fishInTank, false);
			auto foodContainer = new FoodContainer();
			foodContainer->setLocation(QPointF(-4, -2.75));
			foodContainer->setScale(b2Vec2(2, 4));
			addGameObjectToScene(foodContainer, false);
			tank->setWaterLevel(100);
			quests.push(new AddFood());
			break;
		}
		case END:
		{
			auto startOverButton = new StartButton();
			startOverButton->setGraphic(QImage(":/res/start_over_button.png"));
			addGameObjectToScene(startOverButton, false);
			quests.push(new End());
			break;
		}
		default:
			break;
	}

	//Connect quests to the model, so that the model knows when quests are completed.
	for(int i = 0; i < quests.size(); i++){
		Quest* qRef = quests.front();
		connect(qRef, &Quest::pass, this, &FishModel::nextQuest);
		quests.pop();
		quests.push(qRef);
	}

	//Show the instructions of the first quest for this scene.
	if (!quests.empty())
	{
		Quest* qRef = quests.front();
		qRef->showText(constructCallbackOptions());
	}

	//Now that all GameObjects have been instantiated, we can run their start methods.
	std::vector<GameObject*> toStart(gameObjects);

	for(GameObject* gameObject : toStart)
		gameObject->start();
}

/**
 * @brief Collects this GameObject under the mouse if it is the
 * frontmost clickable object.
 * @return Returns true to keep looping through fixtures.
 */
bool FishModel::MouseToPhysicsChecker::ReportFixture(b2Fixture* fixture)
{
	PhysicsGameObject* gameObject = (PhysicsGameObject*) fixture->GetBody()->GetUserData();
	if (gameObject->isClickable())
	{
		if (greatestLayer == nullptr)
			greatestLayer = gameObject;
		else if (greatestLayer->getLayer() < gameObject->getLayer())
			greatestLayer = gameObject;
	}

	return true;
}

/**
 * @brief Returns the GameObject under the mouse of the
 * frontmost clickable object. Returns nullptr if there
 * are no clickable objects under the mouse.
 */
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
	return false;
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
		if (holdObject->isClickable())
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
		if (holdObject->isClickable())
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
	for (auto gameObject: gameObjects)
		deleteGameObject(gameObject->getName());
}


/**
 * @brief Moves on to the proceeding quest. If
 * there are no ore quests to move on to, switch
 * to the next scene.
 */
void FishModel::nextQuest()
{
	auto toDelete = quests.front();
	quests.pop();
	if (!quests.empty())
	{
		auto quest = quests.front();
		quest->showText(constructCallbackOptions());
	}
	delete toDelete;
	if(quests.empty())
		QTimer::singleShot(1000,this, &FishModel::nextTask);
}

/**
 * @brief Keeps track of the fish the player has selected.
 * @param f - The fish to add.
 */
void FishModel::addFishToTank(AnimatedFish* f)
{
	if (fishInTank)
		delete fishInTank;

	fishInTank = new AnimatedFish(*f);
}
