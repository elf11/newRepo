
#ifndef BASEOBJECT__H
#define BASEOBJECT__H

#include "TankIncludes.h"

class Model;

enum ObjectType
{
	otUnknown,
	otTank,
	otPlayerTank,
	otBullet,
	otBuilding,
	otTerrain,
	otSky,
	otPowerUp,
};

class BaseObject
{
private :
public :
	Vector3 pos;
	Vector3 scale;
	Quaternion orient;

	Model *model;

	char *name;

	int todelete;

	int type;

	BaseObject(void);
	~BaseObject(void);

	virtual void Update(void);
	virtual void Render(void);
	virtual void RenderBoundingBox(void);
};

#endif
