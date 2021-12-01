/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  monkeyGameObject
 */
#ifndef FISHTUTORIAL_MONKEYGAMEOBJECT_H
#define FISHTUTORIAL_MONKEYGAMEOBJECT_H

#include <gameobject.h>
#include<Box2D/Box2D.h>

class MonkeyGameObject : public GameObject {
    private:
        b2World world;
        b2Body *body;
    public:
        MonkeyGameObject();
        virtual void updateObject(float);
        ~MonkeyGameObject();
};


#endif //FISHTUTORIAL_MONKEYGAMEOBJECT_H
