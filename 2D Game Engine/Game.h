#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "Box.h"
#include "Sprite.h"
#include "ShaderProgram.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputData.h"
#include "Transform.h"
#include "AudioManager.h"

class Game
{
public:
	Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	void initialize();
	void update();
	void processInput(GLFWwindow *window);
	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);
	static const glm::vec2 * getMouseCoords();
	static b2World* getPhysicsWorld();
	
	static float getDeltaTime()
	{
		return deltaTime;
	}
	static float getTimeSinceStartUp()
	{
		return timeSinceStartUp;
	}
	static void cleanUp()
	{
		GameObject::removeAllGameObjectsFromMemory();
		AudioManager::removeLoadedAudioFromMemory();
		TextureManager::unloadTexturesFromMemory();
	}
	Camera* camera;
	~Game();
private:
	std::chrono::steady_clock clockTime;
	std::vector<GameObject *> gameObjects;
	static GLFWwindow* window;
	static std::unique_ptr<b2World> world;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static glm::vec2 mouseCoord;
};


