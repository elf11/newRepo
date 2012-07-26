#ifndef BUTTON__H
#define BUTTON__H

#include "TankIncludes.h"

class HUDRenderer;

typedef void (*OnButtonAction)(void);

class Button : public HudBaseObject
{
public	:

	OnButtonAction *action;
	
	Texture2D * Texture;

	float posx, posy, width, height;
	float u1, v1, u2, v2;
	float enau1, enav1, enau2, enav2;

	char * text;
	int textLength;

	int enabled, visible, down;

	Button(HudManager *Parent);
	~Button(void);

	int IsInside(int x, int y);
	int OnMouseDown(int x, int y);
	int OnMouseUp(int x, int y);
	int OnMouseMove(int x, int y);
	int OnKeyDown(int key);
	int OnKeyUp(int key);
	void Render(void);

};

#endif