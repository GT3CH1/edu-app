#include "fishmodel.h"
#include <QPoint>

FishModel::FishModel(float _deltaTime) : deltaTime(_deltaTime)
{
	QString monkeFile = ":/stinkyMonkey.png";

	QImage monkeImage(monkeFile);
	GameObject monkey(QPoint(0, 0), 0, monkeImage);
	gameObjects.push_back(monkey);
}

void FishModel::updateGameObjects(){

	std::vector<ObjectRenderInformation> renderables;

	for(GameObject& gameObject : gameObjects)
	{
		gameObject.updateObject(deltaTime);
		ObjectRenderInformation renderInfo {gameObject.getLocation(), gameObject.getRotation(), gameObject.getGraphic()};
		renderables.push_back(renderInfo);
	}

	emit renderGameObjects(renderables);
}
