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
FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime), physicsWorld(b2Vec2(0.0f, -10.0f)) {
    prepareStartUp();

//	{
//		PhysicsGameObject* dropplet = new SimpleDropplet(1, QPointF(0,0), 0, QPointF(0.1,0.1));
//		addGameObjectToScene(dropplet);
//	}

//	{
//		PhysicsGameObject* dropplet2 = new SimpleDropplet(2, QPointF(3,100), 0, QPointF(0.1,0.1));
//		addGameObjectToScene(dropplet2);
//	}
//	{
//		PhysicsGameObject* fishTank = new FishTank("FishTank", QPointF(0,-100), 0, QPointF(0.25,0.25));
//		addGameObjectToScene(fishTank);
//	}
}

/**
 * @brief Sets the scene for start up
 */
void FishModel::prepareStartUp() {
    PhysicsGameObject *fishTank = new FishTank("FishTank", QPointF(0, -100), 0, QPointF(0.25, 0.25));
    addGameObjectToScene(fishTank);

    emit startUp();
}

/**
 * @brief Begins the first task
 */
void FishModel::beginFirstTask() {
    {
        PhysicsGameObject *dropplet = new SimpleDropplet(1, QPointF(0, 0), 0, QPointF(0.1, 0.1));
        addGameObjectToScene(dropplet);
    }

    {
        PhysicsGameObject *dropplet2 = new SimpleDropplet(2, QPointF(3, 100), 0, QPointF(0.1, 0.1));
        addGameObjectToScene(dropplet2);
    }
}

/**
 * @brief Adds a GameObject to the active scene.
 */
void FishModel::addGameObjectToScene(GameObject *toAdd) {
    gameObjects.push_back(toAdd);

    PhysicsGameObject *toAddPhysics = dynamic_cast<PhysicsGameObject *>(toAdd);
    if (toAddPhysics != nullptr)
        addBodyToWorld(toAddPhysics);
}

/**
 * @brief Adds a PhysicsGameObject to the active physics world.
 */
void FishModel::addBodyToWorld(PhysicsGameObject *objectToAdd) {
    b2BodyDef bodyDef = objectToAdd->getBodyDef();
    b2Body *body = physicsWorld.CreateBody(&bodyDef);
    objectToAdd->setBody(body);
}

/**
 * @brief Updates the active scene and sends all the objects
 * that need to be rendered at the end.
 */
void FishModel::updateGameObjects() {
    //Update the physics world.
    physicsWorld.Step(deltaTime, 6, 2);

    //Manage collisions from the physics world.
    b2Contact *contact = physicsWorld.GetContactList();
    int contactCount = physicsWorld.GetContactCount();

    for (int i = 0; i < contactCount; i++) {
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        PhysicsGameObject *gameObjectA = (PhysicsGameObject *) fixtureA->GetBody()->GetUserData();
        PhysicsGameObject *gameObjectB = (PhysicsGameObject *) fixtureB->GetBody()->GetUserData();


        if (fixtureA->IsSensor())
            gameObjectA->onSensor(contact, true, gameObjectB);
        if (fixtureB->IsSensor())
            gameObjectB->onSensor(contact, false, gameObjectA);
        if (!(fixtureA->IsSensor() || fixtureB->IsSensor())) {
            gameObjectA->onCollision(contact, true, gameObjectB);
            gameObjectB->onCollision(contact, false, gameObjectA);
        }

        contact = contact->GetNext();
    }

    //Renderable collects the render data of all active objects.
    std::vector<ObjectRenderInformation> renderables;
    //Hitboxes collects the render data of all fixtures (only used when debug is true).
    std::vector<ObjectRenderInformation> hitBoxes;

    for (GameObject *gameObject: gameObjects) {
        //Update all GameObjects once per frame.
        gameObject->updateObject(deltaTime);

        ObjectRenderInformation renderInfo{gameObject->getLocation(), gameObject->getRotation(), gameObject->getScale(),
                                           gameObject->getGraphic()};
        renderables.push_back(renderInfo);

        //If we're debugging we want to render fixtures.
        if (debug) {
            //Fixtures can only be in PhysicsGameObjects.
            PhysicsGameObject *toPhysics = dynamic_cast<PhysicsGameObject *>(gameObject);
            if (toPhysics != nullptr) {
                b2Fixture *fixture = toPhysics->getBody()->GetFixtureList();

                //Render all fixtures of the current object.
                while (fixture != nullptr) {
                    b2Shape *shape = fixture->GetShape();

                    QColor color = Qt::red;

                    if (fixture->IsSensor())
                        color = Qt::green;

                    //fixtureTranslation is the vector between the center of the body
                    //and the center of this fixture.
                    QPointF fixtureTranslation;
                    QImage fixtureImage = getColliderShape(shape, color, fixtureTranslation);

                    QPointF pos(toPhysics->getBody()->GetPosition().x, toPhysics->getBody()->GetPosition().y);
                    pos += fixtureTranslation;

                    ObjectRenderInformation hitBoxRender{pos, toPhysics->getBody()->GetAngle() * 180 / M_PI,
                                                         QPointF(1, 1), fixtureImage};

                    hitBoxes.push_back(hitBoxRender);

                    fixture = fixture->GetNext();
                }
            }
        }
    }

    //Compiles all things to render together (on release, this loop will be ignored).
    for (ObjectRenderInformation &hitBox: hitBoxes) {
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
QImage FishModel::getColliderShape(b2Shape *shape, QColor penColor, QPointF &translation) {
    QImage shapeImage;

    b2CircleShape *circle = dynamic_cast<b2CircleShape *>(shape);
    b2PolygonShape *polygon = dynamic_cast<b2PolygonShape *>(shape);

    //If we have a circle, just draw a cirlce.
    if (circle != nullptr) {
        shapeImage = QImage(shape->m_radius * 2, shape->m_radius * 2, QImage::Format::Format_RGBA64);
        QPainter painter(&shapeImage);
        painter.setPen(penColor);
        painter.drawEllipse(0, 0, shapeImage.width(), shapeImage.height());
        painter.drawLine(shapeImage.width() / 2, shapeImage.height() / 2, shapeImage.width(), shapeImage.height() / 2);
        painter.end();
        translation = QPointF(circle->m_p.x, circle->m_p.y);
    } else if (polygon != nullptr) //If we have a polygon...
    {
        b2Vec2 last = polygon->m_vertices[0];
        b2Vec2 current;

        //We need to get the bounds of the polygon to make an image...
        QRectF polygonBounds(QPointF(last.x, last.y), QPointF(last.x, last.y));
        //And collect the edges of the polygon.
        std::vector<QLineF> lines;

        for (int i = 1; i < polygon->m_count; i++) {
            current = polygon->m_vertices[i];
            if (current.x < polygonBounds.left())
                polygonBounds = QRectF(QPointF(current.x, polygonBounds.top()),
                                       QPointF(polygonBounds.right(), polygonBounds.bottom()));
            if (current.y < polygonBounds.top())
                polygonBounds = QRectF(QPointF(polygonBounds.left(), current.y),
                                       QPointF(polygonBounds.right(), polygonBounds.bottom()));
            if (current.x > polygonBounds.right())
                polygonBounds = QRectF(QPointF(polygonBounds.left(), polygonBounds.top()),
                                       QPointF(current.x, polygonBounds.bottom()));
            if (current.y > polygonBounds.bottom())
                polygonBounds = QRectF(QPointF(polygonBounds.left(), polygonBounds.top()),
                                       QPointF(polygonBounds.right(), current.y));

            lines.push_back(QLineF(last.x, last.y, current.x, current.y));
            last = current;
        }

        last = polygon->m_vertices[0];
        lines.push_back(QLineF(last.x, last.y, current.x, current.y));

        //Create the image with the polygon's bounds.
        shapeImage = QImage(polygonBounds.width() + 1, polygonBounds.height() + 1, QImage::Format::Format_RGBA64);
        QPainter painter(&shapeImage);
        painter.setPen(penColor);

        QPoint imageCenter(polygonBounds.width() / 2, polygonBounds.height() / 2);
        translation = polygonBounds.center();

        //Draw the edges of the polygon.
        for (QLineF line: lines) {
            painter.drawLine(line.p1() + imageCenter - translation, line.p2() + imageCenter - translation);
        }

        painter.end();
    }

    return shapeImage;
}

/**
 * @brief Destroys this FishModel and all of its objects.
 */
FishModel::~FishModel() {
    for (GameObject *gameObject: gameObjects)
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
    }
}

/**
 * @brief Sets the scene.
 * @param nextScene - The scene to be set.
 */
void FishModel::setScene(SCENE_STATE nextScene) {
    currentScene = FILTER_CHANGE;
    //TODO(gcpease): Somehow update scene on UI.
}
