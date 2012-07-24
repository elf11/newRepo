
#include "platform.h"
#include "GameOptions.h"
#include "Renderer.h"
#include "BaseObject.h"
#include "Cube.h"
#include "Camera.h"
#include "TerainMap.h"

GameOptions *GameOptions::instance = NULL;

GameOptions::GameOptions(void)
{
	instance = this;

	GameRenderer = new Renderer();

	PlayerCamera = new Camera();

	TestCube = new Cube[256];

	int i,j;
	for (i = 0;i < 16;i += 1)
	{
		for (j = 0;j < 16;j += 1)
		{
			TestCube[i * 16 + j].pos.Set(i * 3,j * 3,0);
		}
	}

	TestTerainMap = new TerainMap();
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
