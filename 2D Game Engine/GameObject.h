#pragma once
#include "Sprite.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <vector>
#include <map>
#include "Box.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Component.h"
class GameObject
{
public:
	GameObject();
	GameObject(const std::string& name);
	void setName(const std::string & name) { this->name = name; }
	std::string getName() { return name; }
	void setLayerOrder(int order) { this->layerOrder = order; }
	int getLayerOrder() { return layerOrder; }
	template<class T>
	T *getComponent(void);
	void addComponent(Component *comp);
	template<class T>
	bool hasComponent(void);
	std::vector<Component *> getAttachedComponents() { return components; };
	static GameObject* getGameObjectWithName(const std::string& name)
	{
		return gameObjectMap[name];
	}
	static GameObject* createGameObject(const std::string& name)
	{
		GameObject* gameObject = new GameObject(name);
		gameObjectMap[name] = gameObject;
		return gameObject;
	}
	~GameObject();
private:
	std::string name;
	std::vector<Component *> components;
	int layerOrder;
	static std::map<std::string, GameObject*> gameObjectMap;
};

template<class T>
inline T * GameObject::getComponent(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return (T *)components[i];
	}
	return nullptr;
}

template<class T>
inline bool GameObject::hasComponent(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return true;
	}
	return false;
}
