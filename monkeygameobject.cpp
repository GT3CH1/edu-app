/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  monkeyGameObject
 */
#include "monkeygameobject.h"
MonkeyGameObject::MonkeyGameObject():  world(b2Vec2(0.0f, -10.0f)) {
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -20.0f);
	offset.translate(0, 10);
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body *groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    printf("Init world\n");
}

void MonkeyGameObject::updateObject(float deltaTime) {
//    rotation += deltaTime * 10;
	world.Step(deltaTime, 6, 2);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
	QTransform blank;
	blank.translate(position.x * 20, position.y * 20);
	offset = blank;
	offset.rotate(angle);
}

MonkeyGameObject::~MonkeyGameObject() {
//    delete body;
}
