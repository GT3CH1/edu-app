#include "fishmodel.h"
#include <QPoint>

FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime)
{
	MonkeyGameObject* monkey = new MonkeyGameObject();
	GameObject* omnipotentMonkey = new GameObject();
	gameObjects.push_back(omnipotentMonkey);
	gameObjects.push_back(monkey);
}

void FishModel::updateGameObjects(){

	std::vector<ObjectRenderInformation> renderables;

	for(GameObject* gameObject : gameObjects)
	{
		gameObject->updateObject(deltaTime);
		ObjectRenderInformation renderInfo {gameObject->getOffset(), gameObject->getGraphic()};
		renderables.push_back(renderInfo);
	}

	emit renderGameObjects(renderables);
}

FishModel::~FishModel()
{
	for(GameObject* gameObject : gameObjects)
		delete gameObject;
}
