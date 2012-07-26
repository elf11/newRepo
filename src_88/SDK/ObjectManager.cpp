
#include "TankIncludes.h"

ObjectManager::ObjectManager(void)
{

}

ObjectManager::~ObjectManager(void)
{
	for (int i = 0;i < objects.Length();i += 1)
	{
		delete objects[i];
	}
}

BaseObject *ObjectManager::GetBaseObject(char *Name)
{
	for(unsigned int i = 0; i < objects.Length(); i++)
	{
		if(strcmp(Name,objects[i]->name) == 0)
		{
			return objects[i];
		}
	}
	return NULL;
}
