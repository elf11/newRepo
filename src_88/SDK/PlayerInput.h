#ifndef PLAYERINPUT__H
#define PLAYERINPUT__H

#include "TankIncludes.h"

class PlayerInput
{
public	:
	HudManager *Owner;

	PlayerInput(void);
	~PlayerInput(void);

	void OnMouseDown(int x, int y);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void OnFrame(void);
};

#endif