
#include "TankIncludes.h"

HudManager::HudManager(void)
{
	MouseInit = 0;
	Input = new PlayerInput();
	Input->Owner = this;
	FocusedElement = NULL;
}

HudManager::~HudManager(void)
{
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		delete hudObjects[i];
	}
	delete Input;
}

void HudManager::Render(void)
{
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		hudObjects[i]->Render();
	}
}

void HudManager::MouseDownEvent(int x, int y)
{
	MouseMoveEvent(x,y);
	MouseDown = 1;

	int status = 0;
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		status |= hudObjects[i]->OnMouseDown(x,y);
	}
	if (status == 0)
	{
		Input->OnMouseDown(x,y);
	}
}

void HudManager::MouseUpEvent(int x, int y)
{
	MouseMoveEvent(x,y);
	MouseDown = 0;

	int status = 0;
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		status |= hudObjects[i]->OnMouseUp(x,y);
	}
	if (status == 0)
	{
		Input->OnMouseUp(x,y);
	}
}

void HudManager::MouseMoveEvent(int x, int y)
{
	if (MouseInit == 0)
	{
		MouseInit = 1;
		LastMX = MouseX = x;
		LastMY = MouseY = y;
	}
	else
	{
		LastMX = MouseX;
		LastMY = MouseY;
		MouseX = x;
		MouseY = y;
	}
	DeltaMX = MouseX - LastMX;
	DeltaMY = MouseY - LastMY;

	int status = 0;
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		status |= hudObjects[i]->OnMouseMove(x,y);
	}
	if (status == 0)
	{
		Input->OnMouseMove(x,y);
	}
}

void HudManager::KeyDownEvent(int key)
{
	KeyState[key] = 1;

	int status = 0;
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		status |= hudObjects[i]->OnKeyDown(key);
	}
	if (status == 0)
	{
		Input->OnKeyDown(key);
	}
}

void HudManager::KeyUpEvent(int key)
{
	KeyState[key] = 0;

	int status = 0;
	for (int i = 0; i < hudObjects.Length(); i += 1)
	{
		status |= hudObjects[i]->OnKeyUp(key);
	}
	if (status == 0)
	{
		Input->OnKeyUp(key);
	}
}

void HudManager::FrameEvent(void)
{
	Input->OnFrame();
}
