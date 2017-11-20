#pragma once
class b2World;
#include <GLM\glm.hpp>
#include <memory>
#include <functional>
#include <unordered_map>
#include "InputData.h"
#include "Camera.h"
#include "ShaderProgram.h"

class Game
{
public:
	Game() = delete;
	friend class GameObject;
	static void setUpEngine(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	static void setCursor(const std::string & cursorImagePath);
	static void hideCursor(bool hide);
	static void lockCursor(bool lock);
	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);
	static const glm::vec2 getWindowSize();
	static const glm::vec2 * getMouseCoords();
	static void cleanUp();
	static void setPostProcessingShader(ShaderProgram program);
	static void addScene(std::function<void()> sceneSetupFunc, const std::string & sceneName);
	static void startScene(const std::string & sceneName);
	static b2World* getPhysicsWorld();

	static float getDeltaTime()
	{
		return deltaTime;
	}
	static float getTimeSinceStartUp()
	{
		return timeSinceStartUp;
	}
private:
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static std::unordered_map<std::string, std::function<void()>> scenes;
	static glm::vec2 mouseCoord;
	static glm::vec2 windowSize;
	static ShaderProgram postProcessor;
	struct InternalAcess;
	static std::unique_ptr<InternalAcess> access;
	struct ContactListener;
	static ContactListener* contactListener;
	static void initialize();
	static void update();
};


