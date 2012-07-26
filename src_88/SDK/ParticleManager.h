
#ifndef PARTICLEMANAGER__H
#define PARTICLEMANAGER__H

#include "TankIncludes.h"

class Particle
{
public :
	float Width;
	float Height;
	Vector3 pos;
	Vector3 speed;
	Vector3 accel;
	Color col;
	float ToLive;

	Particle(void);
	~Particle(void);

	void Render(void);
	void Update(void);
};

class ParticleManager
{
public :
	LinkedList<Particle> particles;

	ParticleManager(void);
	~ParticleManager(void);

	void Render(void);
	void Update(void);
};

#endif
