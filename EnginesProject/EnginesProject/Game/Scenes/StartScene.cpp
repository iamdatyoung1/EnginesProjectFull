#include "StartScene.h"
//come back to this
StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	std::cout << "StartScene" << std::endl;
	CoreEngine::GetInstance()->SetCurrentScene(1);

	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
