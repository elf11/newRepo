
#ifndef TANK__H
#define TANK__H

#include "TankIncludes.h"

class GamePlayer;

class Tank: public BaseObject
{
public :
	GamePlayer *Owner;
	Matrix mat;

	Tank(void);
	~Tank(void);

	void Update(void);
	void Render(void);
	void RenderBoundingBox(void);
};

#endif
