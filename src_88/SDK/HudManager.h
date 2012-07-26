
#ifndef HUDMANAGER__H
#define HUDMANAGER__H

#include "TankIncludes.h"

class PlayerInput;

class HudManager
{
public:
	int KeyState[256];
	int MouseInit;
	int MouseDown;
	int MouseRightDown;
	int LastMX,LastMY;
	int MouseX,MouseY;
	int DeltaMX,DeltaMY;

	HudManager(void);
	~HudManager(void);

	PlayerInput *Input;
	Array<HudBaseObject *> hudObjects;

	HudBaseObject *FocusedElement;

	void Render(void);

	void MouseDownEvent(int x, int y);
	void MouseUpEvent(int x, int y);
	void MouseMoveEvent(int x, int y);
	void KeyDownEvent(int key);
	void KeyUpEvent(int key);
	void FrameEvent(void);
};

#endif