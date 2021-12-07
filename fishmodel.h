#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include <vector>
#include <map>
#include "gameobject.h"
#include "objectrenderinformation.h"
#include "monkeygameobject.h"
#include <Box2D/Box2D.h>
#include "physicsgameobject.h"

class FishModel : public QObject {

    Q_OBJECT

    private:
        std::vector<GameObject *> gameObjects;
        std::map<std::string, GameObject *> gameObjectMap;
        float deltaTime;
        b2World physicsWorld;

        void prepareStartUp();
        void addGameObjectToScene(GameObject *toAdd);
        void addBodyToWorld(PhysicsGameObject *toAdd);

        bool debug = true;

        QImage getColliderShape(b2Shape *shape, QColor penColor, QPointF &translation);
        enum SCENE_STATE {
            WATER_CHANGE, FILTER_CHANGE, FEEDING, ADD_FISH, PREPARE_TANK
        };
        // The current scene to draw
        SCENE_STATE currentScene = WATER_CHANGE;
    public:
        FishModel(float deltaTime);
        ~FishModel();

    public slots:
        void updateGameObjects();
        void beginFirstTask();
        void nextTask();

    signals:
        void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
        void startUp();
        void setScene(SCENE_STATE nextScene);
};

#endif // FISHMODEL_H
