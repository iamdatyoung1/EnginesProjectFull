#ifndef COREENGINE_H
#define COREENGINE_H
#include "Window.h"
//in order to gain acces to smart pointers you need to get acces to memory
#include <memory>
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"

#include "../Camera/Camera.h"

class CoreEngine
{
public:
	
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator= (const CoreEngine&) = delete;
	CoreEngine& operator=  (CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	//does not return anything
	void Run();
	//return the varrible for isrunning
	bool GetIsRunning() const;
	void Exit();
	int GetCurrentScene() const;
	//both for camera
	float GetScreenHeight() const;
	float GetScreenWidth() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterFace_);
	void SetCurrentScene(int SceneNum_);
	void SetCamera(Camera* camera_);
private:
	//constructor
	CoreEngine();
	//destructor
	~CoreEngine();
	//takes in a delata time and make sure its a const float so no one touchs it
	void Update(const float deltaTime_);
	//We render to our screen 
	void Render();
	//whateveer we need to clean up goes to the screen
	void OnDestroy();
	static std::unique_ptr<CoreEngine> engineInstance;
	//we set it as friend because we want certain people to see our code
	friend std::default_delete<CoreEngine>;
	//window class that we created
	Window* window;
	//check to see if engine is running or not
	bool isRunning;
	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif