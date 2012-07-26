
#include "TankIncludes.h"

Particle::Particle(void)
{

}

Particle::~Particle(void)
{

}

void Particle::Render(void)
{
	Matrix mat;
	GAME->PlayerCamera->CopyCameraMat(mat);
	mat.Invert();

	Vector3 CameraUp = mat.Up();
	Vector3 CameraRight = mat.Right();

	mat = Matrix::Identity;

	GAME->GameRenderer->SetModel(&mat);

	VertexPosColor Vertices[4];
	Vertices[0].pos = pos + CameraUp * Height / 2 - CameraRight * Width / 2;
	Vertices[1].pos = pos - CameraUp * Height / 2 - CameraRight * Width / 2;
	Vertices[2].pos = pos + CameraUp * Height / 2 + CameraRight * Width / 2;
	Vertices[3].pos = pos - CameraUp * Height / 2 + CameraRight * Width / 2;

/*	Vertices[0].color.Set(rand() % 256,rand() % 256,rand() % 256,255);
	Vertices[1].color.Set(rand() % 256,rand() % 256,rand() % 256,255);
	Vertices[2].color.Set(rand() % 256,rand() % 256,rand() % 256,255);
	Vertices[3].color.Set(rand() % 256,rand() % 256,rand() % 256,255);*/
	Vertices[0].color = col;
	Vertices[1].color = col;
	Vertices[2].color = col;
	Vertices[3].color = col;

	unsigned short Indices[12] = {0,1,2,2,1,3,0,2,1,2,3,1};

	GAME->GameRenderer->DrawBuffer(GL_TRIANGLES,Vertices,Indices,12);
}
	
void Particle::Update(void)
{
	ToLive -= GAME->DeltaFrameTime;
	if (ToLive < 0)
	{
		return;
	}

	pos = pos + (speed * GAME->DeltaFrameTime) + (accel * GAME->DeltaFrameTime * GAME->DeltaFrameTime / 2);
	speed = speed + (accel * GAME->DeltaFrameTime);
}

ParticleManager::ParticleManager(void)
{

}

ParticleManager::~ParticleManager(void)
{
}

void ParticleManager::Render(void)
{
	LinkedNode<Particle> *P = particles.First;
	while (P != NULL)
	{
		P->data.Render();
		P = P->Next;
	}
}

void ParticleManager::Update(void)
{
	LinkedNode<Particle> *P = particles.First;
	while (P != NULL)
	{
		P->data.Update();
		if (P->data.ToLive < 0)
		{
			LinkedNode<Particle> *Temp = P->Next;
			particles.Remove(P);
			P = Temp;
		}
		else
		{
			P = P->Next;
		}
	}
}
