
#include "TankIncludes.h"

BaseObject::BaseObject(void)
{
	pos.Set(0,0,0);
	orient = Quaternion::Identity;
	scale.Set(1.0,1.0,1.0);
	model = NULL;
	todelete = 0;
	type = otUnknown;
	name = NULL;
}

BaseObject::~BaseObject(void)
{
	if (name != NULL)
	{
		free(name);
	}
}

void BaseObject::Update(void)
{

}

void BaseObject::Render(void)
{

}

void BaseObject::RenderBoundingBox(void)
{

}
