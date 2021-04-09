#include "Game1.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	//come back to this
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::FatalError("Engines scene is not intialized to 0", "Game1.h", __LINE__);
	return true;
}

void Game1::Update(const float deltaTime_)
{
	//come back to this
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
	//std::cout << deltaTime_ << std::endl;
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	//come back to this
	delete currentScene;
	currentScene = nullptr;
	
	switch (CoreEngine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}
	//breakpoints to show specific
	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Debug::FatalError("Scene failed to be created", "Game1.h", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}
