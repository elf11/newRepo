
#ifndef LEVELDATA__H
#define LEVELDATA__H

#include "TankIncludes.h"

class MapNodeGraph;

enum TankDataType
{
	tdtPlayer,
	tdtAI,
};

class TeamData
{
public :
	int TeamID;
	char *TeamName;
};

class TankData
{

public :
	TankDataType Type;
	TeamData *Team;

	char *Name;
	char *Model;

	int AI;

	Vector3 Position;
	Quaternion Orientation;
	Vector3 Scale;
};

class BuildingData
{
public :
	TeamData *Team;

	char *Name;
	char *Model;

	int AI;

	Vector3 Position;
	Quaternion Orientation;
	Vector3 Scale;
};

class PropData
{
public :
	char *Name;
	char *Model;

	Vector3 Position;
	Quaternion Orientation;
	Vector3 Scale;
};

class LevelData
{
private :
	TeamData *GetTeam(const char *Name);
public :

	int loaded;

	char *TerrainFileName;
	char *TerrainTexture;
	char *SkyModel;

	float MapWidthRatio;
	float MapHeightRatio;
	float MapVerticalRatio;


	Array<TeamData *> Teams;
	Array<TankData *> Tanks;
	Array<BuildingData *> Buildings;
	Array<PropData *> Props;

	LevelData(void);
	~LevelData(void);

	void LoadFromFile(char *FileName);
};

#endif


/*

Level Data :
 - pozitia si orientarea tancului jucatorului
 - tancurile inamice
 - obiectele (props)
 - dmg,arme

<LevelData>
	<TerrainFileName></TerrainFileName>
	<TerrainTexture></TerrainTexture>
	<SkyModel></SkyModel>

	<Tank>
		<Type></Type>//Player,AI
		<Team></Team>
		<Name></Name>
		<Model></Model>
		<AI></AI>
		<Pos x = "" y = "">
			<X></X>
			<Y></Y>
			<Z></Z>
		</Pos>
		<Orient>
			<X></X>
			<Y></Y>
			<Z></Z>
			<W></W>
		</Orient>
	</Tank>

	<Building>
		<Model></Model>
		<Team></Team>
		<Name></Name>
		<AI></AI>
		<Pos>
			<X></X>
			<Y></Y>
			<Z></Z>
		</Pos>
		<Orient>
			<X></X>
			<Y></Y>
			<Z></Z>
			<W></W>
		</Orient>
	</Building>

	<PropObject>
		<Model></Model>
		<Name></Name>
		<Pos>
			<X></X>
			<Y></Y>
			<Z></Z>
		</Pos>
		<Orient>
			<X></X>
			<Y></Y>
			<Z></Z>
			<W></W>
		</Orient>
	</PropObject>

</LevelData>




<PropObject>
		<Model></Model>
		<Name></Name>
		<Pos>
			<X></X>
			<Y></Y>
			<Z></Z>
		</Pos>
		<Orient>
			<X></X>
			<Y></Y>
			<Z></Z>
			<W></W>
		</Orient>
	</PropObject>

*/
