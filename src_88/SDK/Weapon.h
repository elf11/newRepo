
#ifndef WEAPON__H
#define WEAPON__H

#include "TankIncludes.h"

class Weapon;

class Bullet : public BaseObject
{
public :
	Weapon *Owner;

	Vector3 oldpos;
	Vector3 Velocity;

	Bullet(void);
	~Bullet(void);

	void Update(void);
	void Render(void);
};

class Weapon
{
public :
	float BulletDelay;
	float LastBulletTime;
	Model *BulletModel;

	Weapon(void);
	~Weapon(void);

	bool Fire(Vector3 Position,Vector3 Speed);
};

#endif
