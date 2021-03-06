#include <ParaEngine/Game.h>
#include <GLM\glm.hpp>
#include <ParaEngine/SceneManager.h>
#include <ParaEngine/AudioManager.h>
#include <ParaEngine/TextureLoader.h>
#include <ParaEngine/Sprite.h>
#include <ParaEngine/Text.h>
#include "PlayerMagicController.h"
#include "MagicObjectScaler.h"
#include "ObjectSpawner.h"
#include "SuddenJolt.h"
#include "InitialSceneLogic.h"

extern const std::string IMAGES_PATH = "Test Resources\\Images\\";
extern const std::string FONTS_PATH = "Test Resources\\Fonts\\";
extern const std::string SHADERS_PATH = "Test Resources\\Shaders\\";
extern const std::string AUDIO_PATH = "Test Resources\\Audio\\";

unsigned int texVal1;
unsigned int texVal2;
unsigned int texVal3;

void scene2LoadData();
void scene1LoadData();

int main(int argc, char* argv[])
{
	int ar[] = { 1,4,2,3,7,8,5 };
	for (int i = 0; i < 7; i++)
	{
		int temp = ar[i];
		int j = i;
		while (j > 0 && ar[j] <= ar[j - 1])
		{
			j--;
		}
		temp = ar[j];
		ar[j] = ar[j - 1];
		ar[j - 1] = temp;
	}

	Game::setUpEngine(720, 720, "Para Engine - Game v1.5");
	Game::setVsync(0);
	//Game::setCursor("Test Resources\\cursor.png");
	//game.lockCursor(true);
	//game.hideCursor(true);
	texVal1 = TextureManager::loadTextureFromFile( IMAGES_PATH + "frasa.png", "texOne", false);
	texVal2 = TextureManager::loadTextureFromFile( IMAGES_PATH + "mamma.png", "texTwo", false);
	texVal3 = TextureManager::loadTextureFromFile( IMAGES_PATH + "lili.jpg", "texThree", false);
	TextureManager::loadTextureFromFile( IMAGES_PATH + "goli.png", "translu", false);
	AudioManager::loadAudioFromFile( AUDIO_PATH + "Swoosh.wav", "snd_1");

	Game::addScene(scene2LoadData, "scene1");
	Game::addScene(scene1LoadData, "scene2");
	Game::startScene("scene2", true);

	Game::cleanUp();
	return 0;
}

void scene2LoadData()
{
	PhysicsMaterial physicsMaterial1(0.0f, 0.0f, 1.0f, 0.6f, 0.5f);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Camera");
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new PlayerMagicController);

	Text* textGui = new Text();
	textGui->init( FONTS_PATH + "arial.ttf");
	textGui->text = "This got loaded up in this scene";

	tempGameObject = GameObject::createGameObject("textelement", true);
	tempGameObject->setLayerOrder(1500);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-380, 450));
	tempGameObject->addComponent(textGui);

	tempGameObject = GameObject::createGameObject("BG");
	tempGameObject->setLayerOrder(-10);
	Sprite * tempSprite = new Sprite();
	tempSprite->init(10, 10);
	tempSprite->setTextureID(texVal3);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new ObjectSpawner);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-1, -2));
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);

	tempGameObject = GameObject::createGameObject("FollowMouse");
	tempGameObject->setLayerOrder(10);
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	tempGameObject->addComponent(new MagicObjectScaler);

	Transform* followMouseTransform = tempGameObject->getComponent<Transform>();

	tempGameObject = GameObject::createGameObject("ChildOfFollowMouse");
	tempGameObject->getComponent<Transform>()->setRotation(glm::radians(45.0f));
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(1, 0));

	tempGameObject->getComponent<Transform>()->setParent(followMouseTransform);
	tempGameObject->setLayerOrder(15);
	tempSprite = new Sprite();
	tempSprite->init(0.5f, 0.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);


	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-0.3f, 5.5f));
	tempSprite = new Sprite();
	tempSprite->init(1.5f, 1.5f);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.5f, 1.5f), physicsMaterial1, PhysicsBody::DYNAMIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("PhyMove");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(0.0f, 3.5f));
	tempSprite = new Sprite();
	tempSprite->init(0.4f, 0.4f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(0.4f, 0.4f), physicsMaterial1, PhysicsBody::KINEMATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(0.0f, -5.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(10.0f, 1.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(10.0f, 1.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo1");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-5.5f, -0.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(1.0f, 10.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.0f, 10.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);

	tempGameObject = GameObject::createGameObject("Galoo2");
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(5.5f, -0.0f));
	tempGameObject->setLayerOrder(20);
	tempSprite = new Sprite();
	tempSprite->init(1.0f, 10.0f);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new BoxCollider();
	boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
		glm::vec2(1.0f, 10.0f), physicsMaterial1, PhysicsBody::STATIC);
	tempGameObject->addComponent(boxCollider);
}

void scene1LoadData()
{
	int logoTexValue = TextureManager::loadTextureFromFile( IMAGES_PATH + "paraEngineLogo.png", "logo", false);
	GameObject* tempGameObject;
	tempGameObject = GameObject::createGameObject("Logo");
	Sprite* sprite = new Sprite;
	sprite->init(4.0f, 4.0f);
	sprite->setTextureID(logoTexValue);
	tempGameObject->addComponent(sprite);

	//UI
	tempGameObject = GameObject::createGameObject("gui_1", true);
	tempGameObject->setLayerOrder(1800);
	sprite = new Sprite;
	sprite->init(1.0f, 0.15f);
	sprite->setTextureID(TextureManager::getTextureIdFromReference("translu"));
	tempGameObject->addComponent(sprite);
	tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-0.5f, 0.925f));

	tempGameObject = GameObject::createGameObject("Camera");
	Camera* camera = new Camera;
	camera->init(glm::vec2(10, 10));
	tempGameObject->addComponent(camera);
	tempGameObject->addComponent(new InitialSceneLogic);
}
