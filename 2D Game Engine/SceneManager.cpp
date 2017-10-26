#include "SceneManager.h"
#include <iostream>
#include <string>
#include "Transform.h"
#include "Box.h"
#include "Sprite.h"

SceneManager::SceneManager()
{
}

void SceneManager::SaveSceneData(std::vector<GameObject*> gameObjects, std::string filePath)
{
	//TODO : This wont work
	/*
	Format for serialization:
	-GameObject_Name LayerOrder
	:Component_Type (Transform-eg) constructor arg1 constructor arg2 ....(Special case for Sprite And Box Collider)
	*/
	if (filePath == "s")
	{
		std::cout << "\nSaving to disk";
		std::ofstream save1;
		save1.open("SceneData.para", std::ios::binary);
		save1.seekp(0, std::ios::beg);
		for (int i = 0; i < gameObjects.size(); i++)
		{
			GameObject* gameObject = gameObjects[i];
			std::string data = "\r\n^" + gameObject->getName() + " " + std::to_string(gameObject->getLayerOrder());
			std::vector<Component *> components = gameObject->getAttachedComponents();
			for (int i = 0; i < components.size(); i++)
			{
				std::string type = typeid(*components[i]).name();
				data.append("\r\n:" + type);
				if (typeid(Transform) == typeid(*components[i]))
				{
					Transform * ref = (Transform *)(components[i]);
					data.append(" " + std::to_string(ref->position.x) + " " +
						std::to_string(ref->position.x) + " " +
						std::to_string(ref->rotation) + " " +
						std::to_string(ref->scale.x) + " " +
						std::to_string(ref->scale.y));
				}
				else if (typeid(Sprite) == typeid(*components[i]))
				{
					Sprite* ref = (Sprite *)(components[i]);
					data.append(" " + std::to_string(ref->getDimensions().x) + " " +
						std::to_string(ref->getDimensions().y) + " " +
						std::to_string(1));
				}
				else if (typeid(BoxCollider) == typeid(*components[i]))
				{
					BoxCollider* ref = (BoxCollider *)(components[i]);
					data.append(" " + std::to_string(ref->getBody()->GetPosition().x) + " " +
						std::to_string(ref->getBody()->GetPosition().y) + " " +
						std::to_string(ref->getDimensions().x) + " " +
						std::to_string(ref->getDimensions().y) + " ");
					if (ref->getBody()->GetType() == b2BodyType::b2_staticBody)
						data.append("S");
					else if (ref->getBody()->GetType() == b2BodyType::b2_kinematicBody)
						data.append("K");
					else if (ref->getBody()->GetType() == b2BodyType::b2_dynamicBody)
						data.append("D");
					data.append(" " + std::to_string(1.0f));
				}

			}
			save1.write(data.c_str(), data.size());
		}
		save1.close();
	}
	else
	{
		std::cout << "\n______\n";
		std::ifstream on;
		on.open("SceneData.para", std::ios::binary);
		on.close();
	}
}


SceneManager::~SceneManager()
{
}