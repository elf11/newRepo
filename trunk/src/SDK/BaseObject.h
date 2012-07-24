
#ifndef BASEOBJECT__H
#define BASEOBJECT__H

#include "RMath.h"
#include "Renderer.h"
#include "GameOptions.h"

class BaseObject
{
private :
public :
	Vector3 pos;
	Quaternion orient;

	BaseObject(void);

	virtual void Update(void);
	virtual void Render(void);
};

#endif
