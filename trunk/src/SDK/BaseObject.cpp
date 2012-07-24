
#include "BaseObject.h"

BaseObject::BaseObject(void)
{
 pos.Set(0,0,0);
 orient = Quaternion::Identity;
}

void BaseObject::Update(void)
{

}

void BaseObject::Render(void)
{

}
