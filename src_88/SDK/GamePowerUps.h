
#ifndef GAMEPOWERUPS__H
#define GAMEPOWERUPS__H

#include "TankIncludes.h"

class Model;
class Weapon;
class BaseObject;

enum PowerUpType
{
	ptFanOut,
	ptShootDelay,
	ptDamage,
	ptSpeed,
	ptExplosionRadius,
	ptRange,
	ptMaxHealth,
	ptMaxArmor,
	ptHealth,
	ptArmor,
	ptCriticalStrikeChance,
	ptCriticalStrikeMultiplier,
	ptSize,
	ptInvisibility,
	ptGodMode,
	ptBonusScore,
	ptRespawnDelay,
	ptAmmunition,
	ptPowerUpCount,
};

const int MaxPowerUpLevel = 9;

extern int LevelValues[MaxPowerUpLevel + 1];
extern int FanOutValues[MaxPowerUpLevel + 1];
extern float ShootDelayValues[MaxPowerUpLevel + 1];
extern float DamageValues[MaxPowerUpLevel + 1];
extern float SpeedValues[MaxPowerUpLevel + 1];
extern float ExplosionRadiusValues[MaxPowerUpLevel + 1];
extern float RangeValues[MaxPowerUpLevel + 1];
extern float CriticalStrikeChanceValues[MaxPowerUpLevel + 1];
extern float CriticalStrikeMultiplierValues[MaxPowerUpLevel + 1];
extern float SizeValues[MaxPowerUpLevel + 1];
extern float InvisibilityLevel[MaxPowerUpLevel + 1];

class PowerUp : public BaseObject
{
public :
	PowerUpType powertype;

	int minvalue;
	int maxvalue;

	int addvalue1;
	int addvalue2;
	int addvalue3;

	float animlen;
	float animpos;
	float animminy;
	float animmaxy;

	PowerUp(void);
	~PowerUp(void);

	void Update(void);
	void Render(void);
	void RenderBoundingBox(void);
};

class PowerUpGenerator
{
private :
	PowerUp *CreatePowerUp(void);
	PowerUp *CreatePowerUp(PowerUpType type);
	PowerUp *CreateProbabilitiesPowerUp(PowerUpType type);
public :
	PowerUpGenerator(void);
	~PowerUpGenerator(void);

	int InitialPowerUps;
	float LastTimeGen;
	float MinTimeGen,MaxTimeGen;
	float Probabilities[ptPowerUpCount];

	void Start(void);
	void Update(void);

	//Genereaza in jurul pozitiei CentralPos, Count powerups specificate in List
	void PlacePowerUps(int Count,PowerUpType *List);
	void PlacePowerUps(int Count,Vector3 CentralPos,PowerUpType *List);

	//Genereaza Count power ups random pe harta
	void GenerateRandomPowerUps(int Count);

	//Genereaza Count power ups random in jurul pozitiei
	void GenerateRandomPowerUps(int Count,Vector3 CentralPos);

	//Genereaza Count power ups random in jurul pozitiei, alegand random din acele tipuri
	void GenerateRandomPowerUps(int Count,Vector3 CentralPos,PowerUpType *AvailableTypes,int ListLen);
};

class PowerUpPlayerStatus
{
private :
	void LoosePowerUp(int Index);
public :
	int FanOutLevel;
	int ShootDelayLevel;
	int DamageLevel;
	int SpeedLevel;
	int ExplosionRadiusLevel;
	int RangeLevel;
	int CriticalStrikeChanceLevel;
	int CriticalStrikeMultiplierLevel;
	int SizeLevel;
	int InvisibilityLevel;

	int Score;
	int MaxHealth;
	int MaxArmor;
	int Health;
	int Armor;
	int RespawnDelay;
	int GodModeRemainingTime;

	int WeaponIndex;
	Array<Weapon *> Weapons;

	PowerUpPlayerStatus(void);
	~PowerUpPlayerStatus(void);

	void ApplyPowerUp(PowerUp *pwrup);

	void LooseRandomPowerUps(int Count);
	void LooseAllPowerUps(int Count);
};

#endif
