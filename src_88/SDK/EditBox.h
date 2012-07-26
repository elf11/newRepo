
#ifndef EDITBOX__H
#define EDITBOX__H

#include "TankIncludes.h"

class EditBox : public HudBaseObject
{
public :
	static const int MaxTextLength = 80;

	Texture2D * Texture;
	char text[MaxTextLength + 1];
	int textLength;
	float u1, u2, v1, v2;
	float posx, posy, width, height;

	int focus, enabled, visible;

	EditBox(HudManager *Parent);
	~EditBox(void);

	int IsInside(int x, int y);
	int OnMouseDown(int x, int y);
	int OnMouseUp(int x, int y);
	int OnMouseMove(int x, int y);
	int OnKeyDown(int key);
	int OnKeyUp(int key);
	void Render(void);
};

#endif