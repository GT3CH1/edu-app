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
	addGameObjectLambda = [=](void* toAdd) {this->addGameObjectToScene((GameObject*)toAdd);};
	deleteGameObjectLambda = [=](std::string name) {this->deleteGameObject(name);};
	addJointLambda = [=](b2JointDef* def) {return this->addJoint(def);};
	destroyJointLambda = [=](b2Joint* joint) {this->destroyJoint(joint);};
	getDeltaTimeLambda = [=]() {return this->getDeltaTime();};
	setScene(PREPARE_TANK);
}


/**
 * @brief Creates the quests linked list
 */
void FishModel::createQuests()
{
	// Task 3
	/*
	AddFood* addFood3 = new AddFood();

	quests.push(addFood3);

	// Task 4
	TurnOffWaterPump* turnOffWaterPump4 = new TurnOffWaterPump();
	SwitchFilter* switchFilter4 = new SwitchFilter();
	TurnOnWaterPump* turnOnWaterPump4 = new TurnOnWaterPump();

	quests.push(turnOffWaterPump4);
	quests.push(switchFilter4);
	quests.push(turnOnWaterPump4);

	// Task 5
	ChooseFish* chooseFish5 = new ChooseFish();
	AddFish* addFish5 = new AddFish();

	quests.push(chooseFish5);
	quests.push(addFish5);

	// Task 6
	FillBowl* fillBowl6 = new FillBowl();
	Wait* ageWater6 = new Wait();
	SiphonOldWater* siphon6 = new SiphonOldWater();
	FillTank* fillTank6 = new FillTank();

	quests.push(fillBowl6);
	quests.push(ageWater6);
	quests.push(siphon6);
	quests.push(fillTank6);
	 */
}

CallbackOptions FishModel::constructCallbackOptions()
{
	CallbackOptions options(getGameObjectLambda, addGameObjectLambda, deleteGameObjectLambda, addJointLambda, destroyJointLambda, getDeltaTimeLambda);
	return options;
}

float FishModel::getDeltaTime()
{
	return deltaTime;
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
	if(!gameObjectMap[objectName])
		return;
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

b2Joint* FishModel::addJoint(b2JointDef *jointDefinition)
{
	return physicsWorld.CreateJoint(jointDefinition);
}

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

	b2Joint* joint = physicsWorld.GetJointList();

	while(debug && joint != nullptr)
	{
		b2DistanceJoint* spring = dynamic_cast<b2DistanceJoint*>(joint);
		if (spring)
		{
			b2Vec2 coordinateA(spring->GetLocalAnchorA().x * cos(spring->GetBodyA()->GetAngle()) - spring->GetLocalAnchorA().y * sin(spring->GetBodyA()->GetAngle()),
							   spring->GetLocalAnchorA().x * cos(spring->GetBodyA()->GetAngle()) + spring->GetLocalAnchorA().y * sin(spring->GetBodyA()->GetAngle()));
			coordinateA += spring->GetBodyA()->GetPosition();
			b2Vec2 coordinateB = spring->GetLocalAnchorB() + spring->GetBodyB()->GetPosition();
			b2Vec2 dimensions(abs(coordinateA.x - coordinateB.x), abs(coordinateA.y - coordinateB.y));
			b2Vec2 center((coordinateA.x + coordinateB.x)/2, (coordinateA.y + coordinateB.y)/2);

			QImage image(dimensions.x*20+1, dimensions.y*20+1, QImage::Format::Format_RGBA64);
			image.fill(Qt::transparent);
			QPainter painter(&image);
			painter.setPen(Qt::yellow);
			painter.drawLine((coordinateA.x - center.x)*20 + image.width()/2
							 , -(coordinateA.y - center.y)*20 + image.height()/2
							 , (coordinateB.x - center.x)*20 + image.width()/2,
							 -(coordinateB.y - center.y)*20 + image.height()/2);
			painter.end();
			ObjectRenderInformation info {QPointF(center.x, center.y), 0, QPointF(dimensions.x, dimensions.y), image};
			hitBoxes.push_back(info);
		}
		joint = joint->GetNext();
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
	removeAllGameObjects();
	currentScene = scene;
	auto tank = new Tank();
	auto background = new GameObject("background",QPointF(0,0),0,QPointF(20,14),QImage(":/res/background.png"),0);
	addGameObjectToScene(background);
	addGameObjectToScene(new Filter());
	addGameObjectToScene(new WaterPump());
	addGameObjectToScene(new Countertop(0));
	addGameObjectToScene(tank);
	while(!quests.empty()) {
		delete quests.front();
		quests.pop();
	}
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
			for(auto fish : fishInTank)
			{
				fish.setClickable(false);
				addGameObjectToScene(new Fish(fish));
			}
			break;

		case FEEDING :
			for(auto fish : fishInTank)
			{
				fish.setClickable(false);
				addGameObjectToScene(new Fish(fish));
				auto foodContainer = new FoodContainer();
				foodContainer->setLocation(QPointF(-4,-2.75));
				foodContainer->setScale(b2Vec2(2,4));
				addGameObjectToScene(foodContainer);
			}
			tank->setWaterLevel(100);
			quests.push(new AddFood());
			// food container
			// lots of food
			break;

		case ADD_FISH :
		{
			auto pleco = new Fish();
			pleco->setFishType(Fish::PLECO);
			pleco->setName("pleco");
			pleco->setLocation(QPointF(-9,-3.5));

			auto moorish = new Fish();
			moorish->setFishType(Fish::SIMPLE);
			moorish->setName("moorish");
			moorish->setLocation(QPointF(-6.5,-3.5));

			auto goldfish = new Fish();
			goldfish->setFishType(Fish::GOLDFISH);
			goldfish->setName("goldfish");
			goldfish->setLocation(QPointF(-4,-3.5));
			tank->setWaterLevel(100);
			addGameObjectToScene(pleco);
			addGameObjectToScene(moorish);
			addGameObjectToScene(goldfish);
			addGameObjectToScene(new Clock());

			// Task 2
			quests.push(new ChooseFish());
			quests.push(new AddFish());
			quests.push(new Wait());
			auto removeBagQuest = new RemoveFishFromBag();
			quests.push(removeBagQuest);
			connect((RemoveFishFromBag*)removeBagQuest, &RemoveFishFromBag::fishRemovedFromBag, this,&FishModel::addFishToTank);
			break;
		}
		case PREPARE_TANK :
		{
			addGameObjectToScene(new Clock());
			addGameObjectToScene(new Bowl());
			addGameObjectToScene(new Spigot());
			quests.push(new FillBowl());
			quests.push(new Wait());
			quests.push(new FillTank());
			break;
		}
		default:
			// tank
			// game object water pump
			// game object filter
			break;
	}
	//connect quests with gameObject
	for(int i = 0; i < quests.size(); i++){
		Quest* qRef = quests.front();
		connect(qRef, &Quest::pass, this, &FishModel::nextQuest);
		quests.pop();
		quests.push(qRef);
	}

	if (!quests.empty())
	{
		Quest* qRef = quests.front();
		if(qRef->callShowText){
			qRef->showText(constructCallbackOptions());
		}
	}
}

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

void FishModel::nextQuest()
{
	auto toDelete = quests.front();
	quests.pop();
	if (!quests.empty())
	{
		auto quest = quests.front();
		if(quest->callShowText){
			quest->showText(constructCallbackOptions());
		}
	}
	delete toDelete;
	if(quests.empty())
		QTimer::singleShot(1000,this, &FishModel::nextTask);
}

/**
 * @brief Adds a fish to the current list of fish in this tank.
 * @param f - The fish to add.
 */
void FishModel::addFishToTank(Fish* f)
{
	fishInTank.push_back(*f);
}
