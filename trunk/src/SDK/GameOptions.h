
#ifndef GAMEOPTIONS__H
#define GAMEOPTIONS__H

class Renderer;
class Camera;
class Cube;
class TerainMap;

class GameOptions
{
	static GameOptions *instance;
private:
	GameOptions(void);
public :
	float LastFrameTime;
	float CurrentFrameTime;
	float DeltaFrameTime;

	Renderer *GameRenderer;

	Camera *PlayerCamera;

	Cube *TestCube;		  
	TerainMap *TestTerainMap;

	void InitGameTime(void);
	void UpdateGameTime(void);

	static GameOptions *GetInstance(void);
};

#define GAME GameOptions::GetInstance()

extern int KeyState[256];
extern int MouseDown;
extern int DeltaMX,DeltaMY;

#endif
