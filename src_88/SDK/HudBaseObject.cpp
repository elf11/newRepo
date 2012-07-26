
#include "TankIncludes.h"

HudBaseObject::HudBaseObject(HudManager *Parent)
{
	Owner = Parent;
	Parent->hudObjects.Push(this);
}

HudBaseObject::~HudBaseObject(void)
{
	
}

void HudBaseObject::Render(void)
{

}

int HudBaseObject::OnMouseDown(int x, int y)
{
	return 0;
}

int HudBaseObject::OnMouseUp(int x, int y)
{
	return 0;
}

int HudBaseObject::OnMouseMove(int x, int y)
{
	return 0;
}

int HudBaseObject::OnKeyDown(int key)
{
	return 0;
}

int HudBaseObject::OnKeyUp(int key)
{
	return 0;
}
