
#ifndef CUBEMAP__H
#define CUBEMAP__H

#include "TankIncludes.h"

class SkyBox : public BaseObject
{
public :
	SkyBox(void);
	~SkyBox(void);

	void Update(void);
	void Render(void);
	void RenderBoundingBox(void);
};

#endif
