
#ifndef OBJECTMANAGER__H
#define OBJECTMANAGER__H

#include "TankIncludes.h"

class ObjectManager
{
public :
	ObjectManager(void);
	~ObjectManager(void);

	Array<BaseObject *> objects;

	BaseObject *GetBaseObject(char *Name);
};

#endif
