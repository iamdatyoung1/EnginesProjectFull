#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"
int main(int argc, char* argv[]) 
{
	//We call this function first
	CoreEngine::GetInstance()->SetGameInterface(new Game1());
	if (!CoreEngine::GetInstance()->OnCreate("Game 258 Engine", 800, 600)) {
		std::cout << "Enginefailed" << std::endl;
		return 0;
 }
	CoreEngine::GetInstance()->Run();
	return 0;
}