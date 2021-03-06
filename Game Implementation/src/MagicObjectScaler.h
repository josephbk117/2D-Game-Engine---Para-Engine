#pragma once
#include <ParaEngine/Component.h>
#include <ParaEngine/Transform.h>
#include <ParaEngine/Game.h>
#include <ParaEngine/Camera.h>
class MagicObjectScaler : public Component
{
public:
	virtual void start()
	{
		transform = attachedGameObject->getComponent<Transform>();
		camera = GameObject::getGameObjectWithComponent<Camera>()->getComponent<Camera>();
	}
	virtual void update()
	{
		transform->setScale(glm::vec2(1.0f + abs(sin(Game::getTimeSinceStartUp()*10.0f)), 1.0f));
		transform->setPosition(camera->convertScreenPointToWorldPoint(glm::vec2(Game::getMouseCoords()->x,
			Game::getMouseCoords()->y),
			Game::getWindowSize()));
	}

private:
	Transform* transform = nullptr;
	Camera* camera = nullptr;
};