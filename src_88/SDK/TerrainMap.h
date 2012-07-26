
#ifndef TERAINMAP_H
#define TERAINMAP_H

#include "TankIncludes.h"

class TerrainMapModel : public Model
{
public :
	float *HeightMap;
	int MapWidth,MapHeight;

	TerrainMapModel(ModelManager * Manager) : Model(Manager)
	{
		HeightMap = NULL;
	};
	~TerrainMapModel(void);
	void initializeTerainMap(char *FileName,char *TextureName);

};

class TerrainMap : public BaseObject
{
public :
	float WidthRatio,HeightRatio,VerticalRatio;

	TerrainMap(TerrainMapModel *data);
	~TerrainMap(void);

	const TerrainMapModel * const GetTerrainModel() const { return (TerrainMapModel*)model; }

	float ComputeHeight(float x,float z);
	void ComputeNormal(float x,float z,Vector3 &v);
	void ComputePointPosition(Vector3 &pivot,Vector3 &desired);

	float MaxXPos(void);
	float MaxZPos(void);

	void Update(void);
	void Render(void);
};

#endif