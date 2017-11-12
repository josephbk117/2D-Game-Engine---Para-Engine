#pragma once
#include <Component.h>
#include <Box.h>
#include <Game.h>
#include <iostream>

class SuddenJolt : public Component
{
public:
	virtual void start()
	{
		boxCol = attachedGameObject->getComponent<BoxCollider>();
		physicsMover = GameObject::getGameObjectWithName("PhyMove")->getComponent<BoxCollider>();
	}
	virtual void update()
	{
		if (Game::isKeyPressed(Key::U))
			boxCol->applyForce(glm::vec2(0, 20.0f));
		if (Game::isKeyPressed(Key::J))
			boxCol->applyForce(glm::vec2(0, -200.0f));
		if (Game::isKeyPressed(Key::H))
			boxCol->applyForce(glm::vec2(-80.0f, 0.0f));
		if (Game::isKeyPressed(Key::K))
			boxCol->applyForce(glm::vec2(80.0f, 0.0f));
		if (Game::isKeyPressed(Key::L))
			boxCol->applyTorque(5.0f);
		if (Game::isKeyPressed(Key::N))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x + 0.1*Game::getDeltaTime(), physicsMover->getPosition().y));
		if (Game::isKeyPressed(Key::V))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x - 0.1*Game::getDeltaTime(), physicsMover->getPosition().y));
		if (Game::isKeyPressed(Key::G))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x, physicsMover->getPosition().y + 0.1*Game::getDeltaTime()));
		if (Game::isKeyPressed(Key::B))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x, physicsMover->getPosition().y - 0.1*Game::getDeltaTime()));

	}
	virtual void collisionStarted(GameObject* gameObject)
	{
		std::cout << "\nStarted :: Object Name : " << attachedGameObject->getName().c_str() << " hit against : " << gameObject->getName().c_str();
		boxCol->applyTorque(4.0f);
	}
	virtual void collisionEnded(GameObject* gameObject)
	{
		std::cout << "\nEnded :: Object Name : " << attachedGameObject->getName().c_str() << " hit against : " << gameObject->getName().c_str();
		boxCol->applyTorque(-4.0f);
	}
private:
	BoxCollider* boxCol = nullptr;
	BoxCollider* physicsMover = nullptr;
};