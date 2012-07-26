#ifndef BUILDING__H
#define BUILDING__H

#include "TankIncludes.h"

class Building: public BaseObject
{
public :
	Matrix mat;

	Building(void);
	~Building(void);

	void Update(void);
	void Render(void);
	void RenderBoundingBox(void);
};

#endif