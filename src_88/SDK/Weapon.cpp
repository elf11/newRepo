
#include "TankIncludes.h"

Bullet::Bullet(void)
{
	Velocity.Set(0.0,0.0,0.0);
	pos.Set(0.0,0.0,0.0);
	oldpos.Set(0.0,0.0,0.0);
	Owner = NULL;
	type = otBullet;
}

Bullet::~Bullet(void)
{

}

void Bullet::Update(void)
{
	oldpos = pos;

	Vector3 Gravity;
	Gravity.Set(0.0,-9.8,0.0);
	pos = pos + (Velocity * GAME->DeltaFrameTime) + (Gravity * GAME->DeltaFrameTime * GAME->DeltaFrameTime / 2);
	Velocity = Velocity + (Gravity * GAME->DeltaFrameTime);

	if (GAME->GetTerrain()->ComputeHeight(pos.x,pos.z) > pos.y)
	{
		todelete = 1;
	}
}

void Bullet::Render(void)
{
	Matrix BulletPos;
	Vector3 VelDir = Velocity;
	VelDir.Normalize();
	Matrix::CreateFromYawPitchRoll(VelDir.Yaw(),VelDir.Pitch(),0,&BulletPos);
	BulletPos.Translation() = pos;
	model->Draw(GAME->GameRenderer,&BulletPos);
}

Weapon::Weapon(void)
{
	BulletDelay = 0.0f;
	LastBulletTime = 0.0f;
}

Weapon::~Weapon(void)
{

}

bool Weapon::Fire(Vector3 Position,Vector3 Speed)
{
	if ((LastBulletTime + BulletDelay) < GAME->CurrentFrameTime)
	{
		Bullet *Bl = new Bullet;
		Bl->Velocity = Speed;
		Bl->model = BulletModel;
		Bl->pos = Position;
		Bl->oldpos = Position;
		Bl->name = strdup("Bullet");
		Bl->Owner = this;
		GAME->ObjMan->objects.Push(Bl);
		LastBulletTime = GAME->CurrentFrameTime;
		return true;
	}
	return false;
}
