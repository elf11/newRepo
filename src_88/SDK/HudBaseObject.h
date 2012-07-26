
#ifndef HUDBASEOBJECT__H
#define HUDBASEOBJECT__H

#include "TankIncludes.h"

class HudManager;

enum HudType
{
	htButton,
	htEditBox,
	htLabel,
};

class HudBaseObject
{
public:

	int type;
	HudManager *Owner;

	HudBaseObject(HudManager *Parent);
	~HudBaseObject(void);

	virtual void Render(void);

	virtual int OnMouseDown(int x, int y);
	virtual int OnMouseUp(int x, int y);
	virtual int OnMouseMove(int x, int y);
	virtual int OnKeyDown(int key);
	virtual int OnKeyUp(int key);
};

#endif