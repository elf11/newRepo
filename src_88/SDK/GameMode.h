
#ifndef GAMEOPTIONS__H
#define GAMEOPTIONS__H

class Renderer;
class Camera;
class TextureManager;
class ModelManager;
class Cube;
class TerrainMap;
class TerrainMapModel;
class Model;
class GamePlayer;
class ObjectManager;
class PlayerManager;
class GameHUD;

class GameMode
{
	static GameMode *instance;
private:
	GameMode(void);
public :
	float LastFrameTime;
	float CurrentFrameTime;
	float DeltaFrameTime;

	int WindowWidth,WindowHeight;

	Renderer *GameRenderer;
	Camera *PlayerCamera;

	TextureManager *TexMan;
	ModelManager *ModMan;
	ObjectManager *ObjMan;
	PlayerManager *PlrMan;
	ParticleManager *PtcMan;
	HUDRenderer *TxtRen;

	HudManager *HudMan;
	GameHUD *GameHud;

	MapNodeGraph *AI;

	TerrainMap * GetTerrain() const;

	LevelData lvl;

	bool loaded;
	GamePlayer *Player;

	PowerUpGenerator *PwrGen;

	void InitGameTime(void);
	void UpdateGameTime(void);

	void Update();
	void Render();
	void Load();
	
	static GameMode *GetInstance(void);
};

#define GAME GameMode::GetInstance()

extern int KeyState[256];
extern int MouseDown;
extern int MouseRightDown;
extern int DeltaMX,DeltaMY;

#endif
