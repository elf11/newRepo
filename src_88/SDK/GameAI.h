
#ifndef GAMEAI__H
#define GAMEAI__H

class LevelData;

class MapNode
{
public :

	int IndexInList;
	int TakenInNeighbourFind;
	int AddData3;
	int AddData4;

	Vector3 Pos;

	int NeighboursCount;
	MapNode **Neighbours;

	MapNode *BuildingNeighbours[4];
};

class MapNodeGraph
{
public :
	int NodeCount;
	MapNode *Nodes;

	float *BestDistances;
	MapNode **NextHop;

	int GetIndex(MapNode &From,MapNode &To);

	LevelData *Level;

	MapNodeGraph(void);
	~MapNodeGraph(void);

	void CreateFromLevelData(LevelData *Data);

	void ComputeNeighbours(Vector3 Pos,Array<MapNode *> &Result);
	void ComputePath(Vector3 &Start,Vector3 &End,Vector3 &NextPos);




	void DEBUG_DRAWNEIGHBOURS(void);
};

#endif
