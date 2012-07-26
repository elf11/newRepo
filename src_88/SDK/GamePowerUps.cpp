
#include "TankIncludes.h"

int LevelValues[MaxPowerUpLevel + 1]                      = {    0,    1,    2,    3,    4,    5,    6,    7,    8,    9};
int FanOutValues[MaxPowerUpLevel + 1]                     = {    1,    3,    5,    7,   11,   13,   15,   17,   19,   21};
float ShootDelayValues[MaxPowerUpLevel + 1]               = {    1,  0.9,  0.8,  0.7,  0.6,  0.5,  0.4,0.333, 0.25,  0.2};
float DamageValues[MaxPowerUpLevel + 1]                   = {  1.0, 1.25,  1.5,    2,  2.5,    3,  3.5,    4,  4.5,    5};
float SpeedValues[MaxPowerUpLevel + 1]                    = {  1.0, 1.25,  1.5,    2,  2.5,    3,  3.5,    4,  4.5,    5};
float ExplosionRadiusValues[MaxPowerUpLevel + 1]          = {  1.0,  1.5,    2,  2.5,    3,    4,    5,    6,    7,    8};
float RangeValues[MaxPowerUpLevel + 1]                    = {  1.0,  1.2,  1.4,  1.6,  1.8,    2,  2.2,  2.5,  2.7,    3};
float CriticalStrikeChanceValues[MaxPowerUpLevel + 1]     = {  0.0, 0.05,  0.1, 0.15,  0.2, 0.25,  0.3, 0.35,  0.4,  0.5};
float CriticalStrikeMultiplierValues[MaxPowerUpLevel + 1] = {  1.2,  1.4,  1.7,    2,  2.4,  2.8,  3.2,  3.7,  4.3,  5.0};
float SizeValues[MaxPowerUpLevel + 1]                     = {    1,  0.9,  0.8,  0.7,  0.6,  0.5,  0.4,0.333, 0.25,  0.2};
float InvisibilityLevel[MaxPowerUpLevel + 1]              = {    1,  0.9,  0.8,  0.7,  0.6,  0.5,  0.4,0.333, 0.25,  0.2};

PowerUp::PowerUp(void)
{
	model = GAME->ModMan->GetModel("sphere.glm");
	type = otPowerUp;
	powertype = ptPowerUpCount;

	minvalue = 0;
	maxvalue = 0;

	addvalue1 = 0;
	addvalue2 = 0;
	addvalue3 = 0;

	animlen = 2.0;
	animpos = 0.0;

	animminy = 6.0;
	animmaxy = 12.0;

	scale.Set(5.0,5.0,5.0);
}

PowerUp::~PowerUp(void)
{

}

void PowerUp::Update(void)
{
	animpos += GAME->DeltaFrameTime;
	animpos = Math::Fmod(animpos,animlen);
	orient.RotateY(GAME->DeltaFrameTime);
}

void PowerUp::Render(void)
{
	Matrix mat;
	Matrix::CreateFromQuaternion(&orient,&mat);
	mat.Translation() = pos;
	if (animpos <= (animlen / 2))
	{
		mat.Translation().y += animminy + (animpos * (animmaxy - animminy));
	}
	else
	{
		mat.Translation().y += animminy + ((animlen / 2) * (animmaxy - animminy)) - ((animpos - (animlen / 2)) * (animmaxy - animminy));
	}

	mat.Scale(scale);

	model->Draw(GAME->GameRenderer,&mat);
}

void PowerUp::RenderBoundingBox(void)
{
	Matrix mat;
	Matrix::CreateFromQuaternion(&orient,&mat);
	mat.Translation() = pos;
	if (animpos <= (animlen / 2))
	{
		mat.Translation().y += animminy + (animpos * (animmaxy - animminy));
	}
	else
	{
		mat.Translation().y += animminy + ((animlen / 2) * (animmaxy - animminy)) - ((animpos - (animlen / 2)) * (animmaxy - animminy));
	}

	mat.Scale(scale);

	model->DrawBoundingBox(GAME->GameRenderer,&mat);
}

PowerUpGenerator::PowerUpGenerator(void)
{
	LastTimeGen = 0.0;
	MinTimeGen = 0.1;
	MaxTimeGen = 0.1;
	InitialPowerUps = 30;

	for (int i = 0;i < ptPowerUpCount;i += 1)
	{
		Probabilities[i] = 0.001;
	}
}

PowerUpGenerator::~PowerUpGenerator(void)
{

}

PowerUp *PowerUpGenerator::CreatePowerUp(void)
{
	return CreatePowerUp((PowerUpType)(rand() % ptPowerUpCount));
}

PowerUp *PowerUpGenerator::CreatePowerUp(PowerUpType type)
{
	PowerUp *res = new PowerUp();
	res->powertype = type;
	switch (type)
	{
	case ptFanOut :
		{
		}
		break;
	case ptShootDelay :
		{
		}
		break;
	case ptDamage :
		{
		}
		break;
	case ptSpeed :
		{
		}
		break;
	case ptExplosionRadius :
		{
		}
		break;
	case ptRange :
		{
		}
		break;
	case ptMaxHealth :
		{
			res->minvalue = 200;
			res->maxvalue = 600;
		}
		break;
	case ptMaxArmor :
		{
			res->minvalue = 200;
			res->maxvalue = 600;
		}
		break;
	case ptHealth :
		{
			res->minvalue = 200;
			res->maxvalue = 600;
		}
		break;
	case ptArmor :
		{
			res->minvalue = 200;
			res->maxvalue = 600;
		}
		break;
	case ptCriticalStrikeChance :
		{
		}
		break;
	case ptCriticalStrikeMultiplier :
		{
		}
		break;
	case ptSize :
		{
		}
		break;
	case ptInvisibility :
		{
		}
		break;
	case ptGodMode :
		{
			res->minvalue = 5;
			res->maxvalue = 10;
		}
		break;
	case ptBonusScore :
		{
			res->minvalue = 1000;
			res->maxvalue = 5000;
		}
		break;
	case ptRespawnDelay :
		{
			res->minvalue = 1;
			res->maxvalue = 3;
		}
		break;
	case ptAmmunition :
		{
			//res->minvalue = 2;//nr min de munitie
			//res->maxvalue = 5;//nr max de munitie
			//res->addvalue1 = ;//tipul armei
		}
		break;
	}
	return res;
}

void PowerUpGenerator::Start(void)
{
	for (int i = 0;i < InitialPowerUps;i += 1)
	{
		PowerUp *p = CreatePowerUp();
		float x = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxXPos();
		float z = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxZPos();
		float y = GAME->GetTerrain()->ComputeHeight(x,z);
		p->pos.Set(x,y,z);
		GAME->ObjMan->objects.Push(p);
	}
	LastTimeGen = GAME->CurrentFrameTime;
}

void PowerUpGenerator::Update(void)
{
	int GenCount;
	int Generated[ptPowerUpCount];

	float FrameTime = GAME->CurrentFrameTime - LastTimeGen;
	while (FrameTime >= MaxTimeGen)
	{
		float t = Math::Rand(0.0,1.0);
		float time = MinTimeGen + ((MaxTimeGen - MinTimeGen) * t);

		GenCount = 0;
		for (int i = 0;i < ptPowerUpCount;i += 1)
		{
			if (Math::Rand(0.0,1.0) <= Probabilities[i])
			{
				Generated[i] = 1;
				GenCount += 1;
			}
			else
			{
				Generated[i] = 0;
			}
		}

		if (GenCount > 0)
		{
			int PwrType = rand() % GenCount;
			PowerUpType p;
			for (int i = 0;i < ptPowerUpCount;i += 1)
			{
				if (Generated[i] > 0)
				{
					PwrType -= Generated[i];
					if (PwrType < 0)
					{
						p = ((PowerUpType)(i));
						break;
					}
				}
			}
			PlacePowerUps(1,&p);
		}

		LastTimeGen += time;
		FrameTime -= time;
	}

}

void PowerUpGenerator::PlacePowerUps(int Count,PowerUpType *List)
{
	for (int i = 0;i < Count;i += 1)
	{
		Vector3 pos;
		pos.x = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxXPos();
		pos.z = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxZPos();
		pos.y = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);
		PlacePowerUps(1,pos,List + i);
	}
}

void PowerUpGenerator::PlacePowerUps(int Count,Vector3 CentralPos,PowerUpType *List)
{
	for (int i = 0;i < Count;i += 1)
	{
		PowerUp *p = CreatePowerUp(List[i]);
		p->pos = CentralPos;
		GAME->ObjMan->objects.Push(p);
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count)
{
	for (int i = 0;i < Count;i += 1)
	{
		Vector3 pos;
		pos.x = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxXPos();
		pos.z = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxZPos();
		pos.y = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);
		PowerUp *p = CreatePowerUp();
		p->pos = pos;
		GAME->ObjMan->objects.Push(p);
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count,Vector3 CentralPos)
{
	for (int i = 0;i < Count;i += 1)
	{
		PowerUp *p = CreatePowerUp();
		p->pos = CentralPos;
		GAME->ObjMan->objects.Push(p);
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count,Vector3 CentralPos,PowerUpType *AvailableTypes,int ListLen)
{
	for (int i = 0;i < Count;i += 1)
	{
		PowerUp *p = CreatePowerUp(AvailableTypes[rand() % ListLen]);
		p->pos = CentralPos;
		GAME->ObjMan->objects.Push(p);
	}
}


/*
void PowerUpGenerator::Start(void)
{
	for (int i = 0;i < InitialPowerUps;i += 1)
	{
		PowerUp *p = CreatePowerUp((PowerUpType)(rand() % ptPowerUpCount),AlwaysProbabilities);
		float x = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxXPos();
		float z = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxZPos();
		float y = GAME->GetTerrain()->ComputeHeight(x,z);
		p->pos.Set(x,y,z);
		GAME->ObjMan->objects.Push(p);
	}
	LastTimeGen = GAME->CurrentFrameTime;
}

void PowerUpGenerator::Update(void)
{
	float FrameTime = GAME->CurrentFrameTime - LastTimeGen;
	while (FrameTime >= MaxTimeGen)
	{
		float t = Math::Rand(0.0,1.0);
		float time = MinTimeGen + ((MaxTimeGen - MinTimeGen) * t);
		GenerateRandomPowerUps(1);
		LastTimeGen += time;
		FrameTime -= time;
	}

}

PowerUp *PowerUpGenerator::CreatePowerUp(float *Probabilities)
{
	PowerUp *res = NULL;
	for (int i = 0;(i < ptPowerUpCount) && (res == NULL);i += 1)
	{
		res = CreatePowerUp((PowerUpType)(i),Probabilities);
	}
	return res;
}

PowerUp *PowerUpGenerator::CreatePowerUp(PowerUpType type,float *Probabilities)
{
	if (Math::Rand(0.0,1.0) > Probabilities[type])
	{
		return NULL;
	}
	static int pwrupcount = 0;
	pwrupcount += 1;
	PowerUp *res = new PowerUp();
	res->powertype = type;
	switch (type)
	{
		case ptFanOut :
			{
			}
			break;
		case ptShootDelay :
			{
			}
			break;
		case ptDamage :
			{
			}
			break;
		case ptSpeed :
			{
			}
			break;
		case ptExplosionRadius :
			{
			}
			break;
		case ptRange :
			{
			}
			break;
		case ptMaxHealth :
			{
				res->minvalue = 200;
				res->maxvalue = 600;
			}
			break;
		case ptMaxArmor :
			{
				res->minvalue = 200;
				res->maxvalue = 600;
			}
			break;
		case ptHealth :
			{
				res->minvalue = 200;
				res->maxvalue = 600;
			}
			break;
		case ptArmor :
			{
				res->minvalue = 200;
				res->maxvalue = 600;
			}
			break;
		case ptCriticalStrikeChance :
			{
			}
			break;
		case ptCriticalStrikeMultiplier :
			{
			}
			break;
		case ptSize :
			{
			}
			break;
		case ptInvisibility :
			{
			}
			break;
		case ptGodMode :
			{
				res->minvalue = 5;
				res->maxvalue = 10;
			}
			break;
		case ptBonusScore :
			{
				res->minvalue = 1000;
				res->maxvalue = 5000;
			}
			break;
		case ptRespawnDelay :
			{
				res->minvalue = 1;
				res->maxvalue = 3;
			}
			break;
		case ptAmmunition :
			{
				//res->minvalue = 2;//nr min de munitie
				//res->maxvalue = 5;//nr max de munitie
				//res->addvalue1 = ;//tipul armei
			}
			break;
	}
	return res;
}

void PowerUpGenerator::GeneratePowerUps(int Count,Vector3 CentralPos,PowerUpType *List)
{
	for (int i = 0;i < Count;i += 1)
	{
		float x = Math::Rand(-10.0,10.0) + CentralPos.x;
		float z = Math::Rand(-10.0,10.0) + CentralPos.z;
		float y = GAME->GetTerrain()->ComputeHeight(x,z);
		PowerUp *p = CreatePowerUp(List[i],Probabilities);
		p->pos.Set(x,y,z);
		GAME->ObjMan->objects.Push(p);
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count)
{
	Vector3 p;
	for (int i = 0;i < Count;i += 1)
	{
		p.x = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxXPos();
		p.z = Math::Rand(0.0,1.0) * GAME->GetTerrain()->MaxZPos();
		p.y = GAME->GetTerrain()->ComputeHeight(p.x,p.z);
		GenerateRandomPowerUps(1,p);
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count,Vector3 CentralPos)
{
	while (Count > 0)
	{
		float x = Math::Rand(-10.0,10.0) + CentralPos.x;
		float z = Math::Rand(-10.0,10.0) + CentralPos.z;
		float y = GAME->GetTerrain()->ComputeHeight(x,z);
		PowerUp *p = CreatePowerUp(Probabilities);
		if (p != NULL)
		{
			p->pos.Set(x,y,z);
			GAME->ObjMan->objects.Push(p);
		}
		Count -= 1;
	}
}

void PowerUpGenerator::GenerateRandomPowerUps(int Count,Vector3 CentralPos,PowerUpType *AvailableTypes,int ListLen)
{
	while (Count > 0)
	{
		float x = Math::Rand(-10.0,10.0) + CentralPos.x;
		float z = Math::Rand(-10.0,10.0) + CentralPos.z;
		float y = GAME->GetTerrain()->ComputeHeight(x,z);
		PowerUp *p = CreatePowerUp(AvailableTypes[rand() % ListLen],Probabilities);
		if (p != NULL)
		{
			p->pos.Set(x,y,z);
			GAME->ObjMan->objects.Push(p);
		}
		Count -= 1;
	}
}*/

PowerUpPlayerStatus::PowerUpPlayerStatus(void)
{
	FanOutLevel = 0;
	ShootDelayLevel = 0;
	DamageLevel = 0;
	SpeedLevel = 0;
	ExplosionRadiusLevel = 0;
	RangeLevel = 0;
	CriticalStrikeChanceLevel = 0;
	CriticalStrikeMultiplierLevel = 0;
	SizeLevel = 0;
	InvisibilityLevel = 0;

	Score = 0;
	MaxHealth = 0;
	MaxArmor = 0;
	Health = 0;
	Armor = 0;
	RespawnDelay = 0;
	GodModeRemainingTime = 0;

	WeaponIndex = -1;
}

PowerUpPlayerStatus::~PowerUpPlayerStatus(void)
{

}

void PowerUpPlayerStatus::ApplyPowerUp(PowerUp *pwrup)
{
	switch (pwrup->powertype)
	{
	case ptFanOut :
		{
			FanOutLevel = Math::Min(FanOutLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptShootDelay :
		{
			ShootDelayLevel = Math::Min(ShootDelayLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptDamage :
		{
			DamageLevel = Math::Min(DamageLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptSpeed :
		{
			SpeedLevel = Math::Min(SpeedLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptExplosionRadius :
		{
			ExplosionRadiusLevel = Math::Min(ExplosionRadiusLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptRange :
		{
			RangeLevel = Math::Min(RangeLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptMaxHealth :
		{
			MaxHealth += Math::Rand(pwrup->minvalue,pwrup->maxvalue);
		}
		break;
	case ptMaxArmor :
		{
			MaxArmor += Math::Rand(pwrup->minvalue,pwrup->maxvalue);
		}
		break;
	case ptHealth :
		{
			Health += Math::Min((int)(Math::Rand(pwrup->minvalue,pwrup->maxvalue)),MaxHealth);
		}
		break;
	case ptArmor :
		{
			Armor += Math::Min((int)(Math::Rand(pwrup->minvalue,pwrup->maxvalue)),MaxArmor);
		}
		break;
	case ptCriticalStrikeChance :
		{
			CriticalStrikeChanceLevel = Math::Min(CriticalStrikeChanceLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptCriticalStrikeMultiplier :
		{
			CriticalStrikeMultiplierLevel = Math::Min(CriticalStrikeMultiplierLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptSize :
		{
			SizeLevel = Math::Min(SizeLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptInvisibility :
		{
			InvisibilityLevel = Math::Min(InvisibilityLevel + 1,MaxPowerUpLevel);
		}
		break;
	case ptGodMode :
		{
			GodModeRemainingTime += Math::Rand(pwrup->minvalue,pwrup->maxvalue);
		}
		break;
	case ptBonusScore :
		{
			Score += Math::Rand(pwrup->minvalue,pwrup->maxvalue);
		}
		break;
	case ptRespawnDelay :
		{
			RespawnDelay = Math::Min(RespawnDelay - ((int)(Math::Rand(pwrup->minvalue,pwrup->maxvalue))),0);
		}
		break;
	case ptAmmunition :
		{
			//adauga munitia
		}
		break;
	}
}

void PowerUpPlayerStatus::LoosePowerUp(int Index)
{
#define RemovePowerUp(x) {\
							Index -= x;\
							if ((Index <= 0) && (x > 0))\
							{\
								x -= 1;\
								return;\
							}\
						}

	RemovePowerUp(FanOutLevel);
	RemovePowerUp(ShootDelayLevel);
	RemovePowerUp(DamageLevel);
	RemovePowerUp(SpeedLevel);
	RemovePowerUp(ExplosionRadiusLevel);
	RemovePowerUp(RangeLevel);
	RemovePowerUp(CriticalStrikeChanceLevel);
	RemovePowerUp(CriticalStrikeMultiplierLevel);
	RemovePowerUp(SizeLevel);
	RemovePowerUp(InvisibilityLevel);

#undef RemovePowerUp(x)

}

void PowerUpPlayerStatus::LooseRandomPowerUps(int Count)
{
	int TotalLevel = FanOutLevel + ShootDelayLevel + DamageLevel + SpeedLevel +
					 ExplosionRadiusLevel + RangeLevel + CriticalStrikeChanceLevel + 
					 CriticalStrikeMultiplierLevel + SizeLevel + InvisibilityLevel;
	for (int i = 0;(i < Count) && (TotalLevel > 0);i += 1)
	{
		LoosePowerUp(rand() % TotalLevel);
		TotalLevel -= 1;
	}

}

void PowerUpPlayerStatus::LooseAllPowerUps(int Count)
{
#define RemovePowerUp(x) x = Math::Min(0,x - Count);

	RemovePowerUp(FanOutLevel);
	RemovePowerUp(ShootDelayLevel);
	RemovePowerUp(DamageLevel);
	RemovePowerUp(SpeedLevel);
	RemovePowerUp(ExplosionRadiusLevel);
	RemovePowerUp(RangeLevel);
	RemovePowerUp(CriticalStrikeChanceLevel);
	RemovePowerUp(CriticalStrikeMultiplierLevel);
	RemovePowerUp(SizeLevel);
	RemovePowerUp(InvisibilityLevel);

#undef RemovePowerUp
}
