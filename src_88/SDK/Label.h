
#ifndef LABEL__H
#define LABEL__H

#include "TankIncludes.h"

class Label : public HudBaseObject
{
public:
	float posx, posy, width, height;
	char * text;
	int textLength;
	int visible;

	Label(HudManager *Parent);
	~Label(void);

	void Render(void);

};

#endif