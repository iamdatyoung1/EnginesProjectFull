#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(60), gameInterface(nullptr), currentSceneNum(0)
{
}

CoreEngine::~CoreEngine()
{
}

CoreEngine* CoreEngine::GetInstance() 
{
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	//our debbuger class is complety static so we dont need any pointers we can just output the debugger oncreate
	//Static allows you to not use any kind of pointer example window->oncreate
	Debug::OnCreate();
	window = new Window();
	//create window
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to intialize", "CoreEngine.cpp", __LINE__);
		//Destroy it to clean up
		OnDestroy();
		//return to vaule of false
		return isRunning = false;
	}
	ShaderHandler::GetInstance()->CreateProgram("colourShader", 
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");
	
	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");
	//if the gameinterface is not creating the pull up the string game failed and call ondestroy
	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Warning("Gane failed to initialize", "CoreEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}
	//Dont need this but it is good to have cause it allows you to know if it worked or not
	Debug::Info("Everything worked", "CoreEngine.cpp", __LINE__);
	timer.Start();
	//if the creation of the window works properly then return isRunning varrible to true 
	return isRunning = true;
}

void CoreEngine::Run()
{
	//Loop isRunning constaly update and render
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
	
		//always call update before anything for the purpose of always updating time
		//0.016 is actually 60 frames the reaon is because 1 deived by 60 would give you this number
		
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	//if isRunning is not set in motion then just Destroy
	//dont really need !isrunning but we use it anyways to make it perfectly clear
	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{

	return isRunning;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterFace_)
{
	//this is just allowing us to set it to the pointer that is getting passed through 
	gameInterface = gameInterFace_;
}

void CoreEngine::SetCurrentScene(int SceneNum_)
{
	currentSceneNum = SceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::Update(const float deltaTime_)
{
	//outputs all the numbers on the debugger
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
		//std::cout << deltaTime_ << std::endl;
	}

}

void CoreEngine::Render()
{
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->Render();
	}
	//Call Game Render
	SDL_GL_SwapWindow(window->GetWindow());

}

void CoreEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	//allows destroy from inside out 
	delete camera;
	camera = nullptr;
	delete gameInterface;
	gameInterface = nullptr;
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
