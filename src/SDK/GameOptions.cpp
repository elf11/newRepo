
#include "platform.h"
#include "GameOptions.h"
#include "Renderer.h"
#include "BaseObject.h"
#include "Cube.h"
#include "Camera.h"

GameOptions *GameOptions::instance = NULL;

GameOptions::GameOptions(void)
{
	instance = this;

	GameRenderer = new Renderer();

	PlayerCamera = new Camera();

	TestCube = new Cube();
}

void GameOptions::InitGameTime(void)
{
	LastFrameTime = GetTime();
	CurrentFrameTime = LastFrameTime;
	DeltaFrameTime = 0;
}

void GameOptions::UpdateGameTime(void)
{
	LastFrameTime = CurrentFrameTime;
	CurrentFrameTime = GetTime();
	DeltaFrameTime = CurrentFrameTime - LastFrameTime;
}

GameOptions *GameOptions::GetInstance(void)
{
	if (GameOptions::instance == NULL)
	{
		GameOptions::instance = new GameOptions();
	}
	return instance;
}
