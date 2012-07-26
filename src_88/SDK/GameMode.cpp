
#include <fstream>
#include <string>
#include "platform.h"
#include "TankIncludes.h"
#include "LevelData.h"

using namespace std;

GameMode *GameMode::instance = NULL;

GameMode::GameMode(void)
{
	instance = this;
	loaded = false;
}

void GameMode::InitGameTime(void)
{
	LastFrameTime = GetTime();
	CurrentFrameTime = LastFrameTime;
	DeltaFrameTime = 0;
}

void GameMode::UpdateGameTime(void)
{
	LastFrameTime = CurrentFrameTime;
	CurrentFrameTime = GetTime();
	DeltaFrameTime = CurrentFrameTime - LastFrameTime;
}

GameMode *GameMode::GetInstance(void)
{
	if (GameMode::instance == NULL)
	{
		GameMode::instance = new GameMode();
	}
	return instance;
}

void GameMode::Load()
{
	loaded = 1;

	GameRenderer = new Renderer();

	TexMan = new TextureManager();
	ModMan = new ModelManager(TexMan,GameRenderer);
	ObjMan = new ObjectManager();
	PlrMan = new PlayerManager();
	PtcMan = new ParticleManager();
	TxtRen = new HUDRenderer();

	TxtRen->LoadTextData("FontImage.png","FontData.txt");

	lvl.LoadFromFile("../res/level.xml");

	CubeModel *Cube = new CubeModel(ModMan);
	Cube->initCube();



	Model *SkyModel = new Model(ModMan);
	SkyModel->LoadFromFile(lvl.SkyModel,TexMan);

	SkyBox *Sky = new SkyBox();
	Sky->name = "Sky";
	Sky->model = SkyModel;

	ObjMan->objects.Push(Sky);



	TerrainMapModel *TerrainModel = new TerrainMapModel(ModMan);
	TerrainModel->initializeTerainMap(lvl.TerrainFileName,lvl.TerrainTexture);

	TerrainMap *map = new TerrainMap(TerrainModel);
	map->model = TerrainModel;
	map->name = strdup("Terrain");
	map->pos.Set(0,0,0);
	map->WidthRatio = lvl.MapWidthRatio;
	map->HeightRatio = lvl.MapHeightRatio;
	map->VerticalRatio = lvl.MapVerticalRatio;
	ObjMan->objects.Push(map);



	for (int i = 0;i < lvl.Tanks.Length();i += 1)
	{
		Tank *tank = new Tank();
		tank->model = ModMan->GetModel(lvl.Tanks[i]->Model);
		tank->pos = lvl.Tanks[i]->Position;
		tank->name = strdup(lvl.Tanks[i]->Name);
		tank->orient = lvl.Tanks[i]->Orientation;

		ObjMan->objects.Push(tank);

		if (lvl.Tanks[i]->Type == tdtPlayer)
		{
			tank->type = otPlayerTank;

			GamePlayer *SelfPlayer = new GamePlayer();
			SelfPlayer->type = GamePlayer::GAMEPLAYER_MAIN;
			SelfPlayer->name = strdup("Self");
			SelfPlayer->SetControlledObject(tank);

			SelfPlayer->weap = new Weapon();
			SelfPlayer->weap->BulletDelay = 1.0f;
			SelfPlayer->weap->BulletModel = ModMan->GetModel("Basic Cube");

			GAME->Player = SelfPlayer;

			PlrMan->AddPlayer(SelfPlayer);

			PlayerCamera = new Camera();
			PlayerCamera->Change(Camera::CAMERA_3RDPERSON,tank);
		}
		else
		{
			tank->type = otTank;

			GamePlayer *SelfPlayer = new GamePlayer();
			SelfPlayer->type = GamePlayer::GAMEPLAYER_AI;
			SelfPlayer->name = strdup("AI1");
			SelfPlayer->SetControlledObject(tank);

			PlrMan->AddPlayer(SelfPlayer);
		}
	}

	for (int i = 0;i < lvl.Buildings.Length();i += 1)
	{
		Building *building = new Building();
		building->model = ModMan->GetModel(lvl.Buildings[i]->Model);
		building->pos = lvl.Buildings[i]->Position;
		building->scale= lvl.Buildings[i]->Scale;
		building->name = strdup(lvl.Buildings[i]->Name);
		building->orient = lvl.Buildings[i]->Orientation;

		ObjMan->objects.Push(building);
	}

	PwrGen = new PowerUpGenerator();
	PwrGen->Start();

	HudMan = new HudManager();
	GameHud = new GameHUD();


	for (int i = 0;i < 0;i += 1)
	{
		Tank *tank = new Tank();
		tank->model = ModMan->GetModel("tank02_de.glm");


		float posx = (float)(rand()) / 32768;
		float posz = (float)(rand()) / 32768;
		posx *= 0.8;
		posx += 0.1;
		posz *= 0.8;
		posz += 0.1;
		posx *= ((GAME->GetTerrain())->GetTerrainModel()->MapWidth * GAME->GetTerrain()->WidthRatio);
		posz *= ((GAME->GetTerrain())->GetTerrainModel()->MapHeight * GAME->GetTerrain()->HeightRatio);

		tank->name = strdup("AI tank 1");
		tank->orient = Quaternion::Identity;

		ObjMan->objects.Push(tank);

		GamePlayer * SelfPlayer = new GamePlayer();
		SelfPlayer->type = GamePlayer::GAMEPLAYER_AI;
		SelfPlayer->name = strdup("AI1");
		SelfPlayer->SetControlledObject(tank);
		SelfPlayer->object->pos.Set(posx,GAME->GetTerrain()->ComputeHeight(posx,posz),posz);
		PlrMan->AddPlayer(SelfPlayer);
	}

	AI = new MapNodeGraph();
	AI->CreateFromLevelData(&lvl);
	

}

void GameMode::Update()
{
	UpdateGameTime();

	Vector3 oldpos = GAME->Player->object->pos;
	Quaternion oldorient = GAME->Player->object->orient;

	GAME->HudMan->FrameEvent();
	GAME->GameHud->UpdatePowerUpsStatusLabels();

	for (int i = 0;i < PlrMan->players.Length();i += 1)
	{
		PlrMan->players[i]->Update();
	}

	for (int i = 0;i < ObjMan->objects.Length();i += 1)
	{
		if (ObjMan->objects[i]->todelete != 0)
		{
			delete ObjMan->objects[i];
			ObjMan->objects.RemoveNo(i);
			i -= 1;
			continue;
		}
		ObjMan->objects[i]->Update();
	}

	PwrGen->Update();

	if (ObjMan->objects.Length() > 0)
	{

		int *Collided = new int[ObjMan->objects.Length()];
		for (int i = 0;i < ObjMan->objects.Length();i += 1)
		{
			Collided[i] = 0;
		}
		for (int i = 0;i < ObjMan->objects.Length();i += 1)
		{
			if ((ObjMan->objects[i]->type != otTank) && (ObjMan->objects[i]->type != otPlayerTank) && (ObjMan->objects[i]->type != otBullet))
			{
				continue;
			}
			for (int j = 0;j < ObjMan->objects.Length();j += 1)
			{
				if (i == j)
				{
					continue;
				}
				if (ObjMan->objects[j]->type == otTerrain)
				{
					continue;
				}
				if (ObjMan->objects[j]->type == otUnknown)
				{
					continue;
				}
				if (ObjMan->objects[j]->type == otSky)
				{
					continue;
				}
				if (ObjMan->objects[j]->type == otPowerUp)
				{
					if (ObjMan->objects[i]->type == otPlayerTank)
					{
						if (GameIntersection::Box3Box3(ObjMan->objects[i],ObjMan->objects[j]))
						{
							Tank *Tnk = ((Tank *)(ObjMan->objects[i]));
							PowerUp *pu = ((PowerUp *)(ObjMan->objects[j]));
							Tnk->Owner->PowerUps.ApplyPowerUp(pu);
							Collided[j] = 1;
						}
					}
					continue;
				}
				if (ObjMan->objects[i]->type == otBullet)
				{
					if (ObjMan->objects[j]->type == otBullet)
					{
						continue;
					}
					else
					{
						if ((ObjMan->objects[j]->type == otTank) || (ObjMan->objects[j]->type == otPlayerTank))
						{
							Bullet *Bul = ((Bullet *)(ObjMan->objects[i]));
							Tank *Tnk = ((Tank *)(ObjMan->objects[j]));
							if (Bul->Owner == Tnk->Owner->weap)
							{
								continue;
							}
						}
						float time = GameIntersection::RayBox3(ObjMan->objects[j],((Bullet *)(ObjMan->objects[i]))->oldpos,ObjMan->objects[i]->pos);
						if (time < 0)
						{
							continue;
						}
						Collided[i] = 1;
						Bullet *Bul = ((Bullet *)(ObjMan->objects[i]));
						Bul->pos = Bul->oldpos + ((Bul->pos - Bul->oldpos) * time);
						if (ObjMan->objects[j]->type == otTank)
						{
							Collided[j] = 1;
						}
					}
				}
				else
				{
					if (ObjMan->objects[j]->type == otBullet)
					{
						if ((ObjMan->objects[i]->type == otTank) || (ObjMan->objects[i]->type == otPlayerTank))
						{
							Bullet *Bul = ((Bullet *)(ObjMan->objects[j]));
							Tank *Tnk = ((Tank *)(ObjMan->objects[i]));
							if (Bul->Owner == Tnk->Owner->weap)
							{
								continue;
							}
						}
						float time = GameIntersection::RayBox3(ObjMan->objects[i],((Bullet *)(ObjMan->objects[j]))->oldpos,ObjMan->objects[j]->pos);
						if (time < 0)
						{
							continue;
						}
						Collided[j] = 1;
						Bullet *Bul = ((Bullet *)(ObjMan->objects[j]));
						Bul->pos = Bul->oldpos + ((Bul->pos - Bul->oldpos) * time);
						if (ObjMan->objects[i]->type == otTank)
						{
							Collided[i] = 1;
						}
					}
					else
					{
						if (GameIntersection::Box3Box3(ObjMan->objects[i],ObjMan->objects[j]))
						{
							if (ObjMan->objects[i]->type == otPlayerTank)
							{
								GAME->Player->object->pos = oldpos;
								GAME->Player->object->orient = oldorient;
								GAME->Player->speed.Set(0.0,0.0,0.0);
								GAME->Player->object->Update();
							}
							if (ObjMan->objects[i]->type == otTank)
							{
								Collided[i] = 1;
							}
							if (ObjMan->objects[j]->type == otTank)
							{
								Collided[j] = 1;
							}
							if (ObjMan->objects[i]->type == otBullet)
							{
								Collided[i] = 1;
							}
							if (ObjMan->objects[j]->type == otBullet)
							{
								Collided[j] = 1;
							}
						}
					}
				}
			}
		}

		for (int i = ObjMan->objects.Length() - 1;i >= 0;i -= 1)
		{
			if (Collided[i] == 1)
			{
				if (ObjMan->objects[i]->type == otBullet)
				{
					Vector3 Wind;
					Wind.Set(rand() % 50 - 25,rand() % 10,rand() % 50 - 25);
					for (int k = 0;k < 100;k += 1)
					{
						LinkedNode<Particle> *P = new LinkedNode<Particle>();
						P->data.Height = 10.0;
						P->data.Width = 10.0;
						P->data.pos = ObjMan->objects[i]->pos;
						P->data.speed.Set(rand() % 30 - 15,
							              rand() % 30,
							              rand() % 30 - 15);
						P->data.accel = Wind;
//						P->data.accel.y *= 2;
						P->data.ToLive = ((float)(rand() % 7000)) / 700;
						P->data.col.Set(rand() % 256,rand() % 256,rand() % 256,255);
						GAME->PtcMan->particles.AppendRight(P);
					}
				}
				ObjMan->objects.RemoveNo(i);
			}
			else
			{
				if ((ObjMan->objects[i]->type == otBullet) &&
					(ObjMan->objects[i]->pos.y < GAME->GetTerrain()->ComputeHeight(ObjMan->objects[i]->pos.x,ObjMan->objects[i]->pos.z)))
				{
					Vector3 Wind;
					Wind.Set(rand() % 50 - 25,rand() % 10,rand() % 50 - 25);
					for (int k = 0;k < 100;k += 1)
					{
						LinkedNode<Particle> *P = new LinkedNode<Particle>();
						P->data.Height = 10.0;
						P->data.Width = 10.0;
						P->data.pos = ObjMan->objects[i]->pos;
						P->data.speed.Set(rand() % 30 - 15,
							              rand() % 30,
							              rand() % 30 - 15);
						P->data.accel = Wind;
//						P->data.accel.y *= 2;
						P->data.ToLive = ((float)(rand() % 7000)) / 700.0f;
						P->data.col.Set(rand() % 256,rand() % 256,rand() % 256,255);
						GAME->PtcMan->particles.AppendRight(P);
					}
				}
			}
		}
		delete[] Collided;

	}

	PtcMan->Update();

	PlayerCamera->Update();
}

void GameMode::Render()
{
	glClearColor(0.0f, 0.3f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	PlayerCamera->Render();

	for (int i = 0;i < ObjMan->objects.Length();i += 1)
	{
		ObjMan->objects[i]->Render();
	}

	PtcMan->Render();

	glDisable(GL_DEPTH_TEST);
	for (int i = 0;i < ObjMan->objects.Length();i += 1)
	{
		ObjMan->objects[i]->RenderBoundingBox();
	}
	glEnable(GL_DEPTH_TEST);




	glDisable(GL_DEPTH_TEST);
	AI->DEBUG_DRAWNEIGHBOURS();
	HudMan->Render();
	glEnable(GL_DEPTH_TEST);

	Vector3 pos;
	pos.Set(500.0,0.0,500.0);
	Array<MapNode *> Points;
	GAME->AI->ComputeNeighbours(pos,Points);
}

TerrainMap * GameMode::GetTerrain() const
{
	return(TerrainMap *)(GAME->ObjMan->GetBaseObject("Terrain"));
}
