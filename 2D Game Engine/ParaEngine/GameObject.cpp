#include "GameObject.h"
#include "Transform.h"
#include "Box.h"
#include <iostream>

#if _DEBUG
#include "ParaEngineError.h"
#endif

std::unordered_map<std::string, GameObject*> GameObject::gameObjectMap;
std::vector<GameObject *> GameObject::gameObjectVector;
std::vector<GameObject *> GameObject::objectsMarkedForDeletion;
bool GameObject::isDirty = false;

GameObject::GameObject()
{
	this->name = "";
	this->layerOrder = 0;
}

GameObject::GameObject(const std::string & name)
{
	this->name = name;
}

void GameObject::setName(const std::string & name) noexcept
{
	isDirty = true;
	this->name = name;
}

const std::string & GameObject::getName() const noexcept
{
	return name;
}

void GameObject::setLayerOrder(int order) noexcept
{
	isDirty = true;
	this->layerOrder = order;
}

const int GameObject::getLayerOrder() const noexcept
{
	return layerOrder;
}

void GameObject::addComponent(Component * comp)
{
#if _DEBUG
	if (typeCountMap.find(std::string(typeid(*comp).name())) == typeCountMap.end())
		typeCountMap[std::string(typeid(*comp).name())] = 0;
	else
	{
		typeCountMap[std::string(typeid(*comp).name())] = typeCountMap[std::string(typeid(*comp).name())] + 1;
		throw(ParaEngineError(ParaErrorType::COMPONENT_ALREADY_PRESENT, "Component Already Present"));
	}
#endif

	comp->attachedGameObject = this;
	components.push_back(comp);
}
const std::vector<Component*>& GameObject::getAttachedComponents()
{
	return components;
}
GameObject * GameObject::getGameObjectWithName(const std::string & name)
{
	return gameObjectMap[name];
}
GameObject * GameObject::createGameObject(const std::string & name, bool isUI)
{
#if _DEBUG
	if (gameObjectMap.find(name) != gameObjectMap.end())
		throw(ParaEngineError(ParaErrorType::OBJECT_NAME_ALREADY_PRESENT, "Object Name Already Present"));
#endif
	isDirty = true;
	GameObject* gameObject = new GameObject(name);
	gameObject->addComponent(new Transform);
	gameObject->isPartOfUI = isUI;
	gameObjectMap[name] = gameObject;
	gameObjectVector.push_back(gameObject);
	return gameObject;
}
const std::vector<GameObject*>& GameObject::getAllGameObjects() noexcept
{
	return gameObjectVector;
}
void GameObject::deleteGameObjectWithName(const std::string & name)
{
	if (gameObjectMap.find(name) == gameObjectMap.end())
		return;
	bool canAdd = true;
	const unsigned int objDeletionSize = objectsMarkedForDeletion.size();
	for (unsigned int i = 0; i < objDeletionSize; i++)
	{
		if (gameObjectMap[name] == objectsMarkedForDeletion[i])
		{
			canAdd = false;
			break;
		}
	}
	if (canAdd)
	{
		objectsMarkedForDeletion.push_back(gameObjectMap[name]);
		isDirty = true;
	}
}
void GameObject::deleteGameObjectWithNameImmediate(const std::string & name)
{
	unsigned int size = gameObjectVector.size();
	int pos = -1;
	for (unsigned int i = 0; i < size; i++)
	{
		if (gameObjectVector[i] == gameObjectMap[name])
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
		return;
	gameObjectVector.erase(gameObjectVector.begin() + pos);
	delete gameObjectMap[name];
	gameObjectMap.erase(name);
}
void GameObject::removeAllGameObjectsFromMemory()
{
	const unsigned int sizeValue = gameObjectVector.size();
	for (unsigned int i = 0; i < sizeValue; i++)
		delete gameObjectVector[i];
	clearGameObjectData();
}
void GameObject::clearGameObjectData()
{
	gameObjectMap.clear();
	gameObjectVector.clear();
	objectsMarkedForDeletion.clear();
}
void GameObject::removeAllObjectsMarkedForDeletion()
{
	if (objectsMarkedForDeletion.size() <= 0)
		return;
	const unsigned int deletionSize = objectsMarkedForDeletion.size();
	for (unsigned int i = 0; i < deletionSize; i++)
	{
		const unsigned int gameVecObjSize = gameObjectVector.size();
		for (unsigned int j = 0; i < gameVecObjSize; j++)
		{
			if (objectsMarkedForDeletion[i] != nullptr)
			{
				if (gameObjectVector[j] == objectsMarkedForDeletion[i])
				{
					gameObjectMap.erase(objectsMarkedForDeletion[i]->getName());
					delete objectsMarkedForDeletion[i];
					break;
				}
			}
		}
	}

	gameObjectVector.clear();
	for (auto it = gameObjectMap.begin(); it != gameObjectMap.end(); ++it)
	{
		if (it->second != nullptr)
			gameObjectVector.push_back(it->second);
	}
	objectsMarkedForDeletion.clear();
}

GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); i++)
		delete components[i];
}
