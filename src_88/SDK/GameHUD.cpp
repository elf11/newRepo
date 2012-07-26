
#include "TankIncludes.h"

GameHUD::GameHUD(void)
{
	FanOutStatusLabel = new Label(GAME->HudMan);
	FanOutStatusLabel->posx = 100;
	FanOutStatusLabel->posy = 24;
	FanOutStatusLabel->width = 300;
	FanOutStatusLabel->height = 16;
	FanOutStatusLabel->visible = 1;

	ShootDelayStatusLabel = new Label(GAME->HudMan);
	ShootDelayStatusLabel->posx = 100;
	ShootDelayStatusLabel->posy = 40;
	ShootDelayStatusLabel->width = 300;
	ShootDelayStatusLabel->height = 16;
	ShootDelayStatusLabel->visible = 1;

	DamageStatusLabel = new Label(GAME->HudMan);
	DamageStatusLabel->posx = 100;
	DamageStatusLabel->posy = 56;
	DamageStatusLabel->width = 300;
	DamageStatusLabel->height = 16;
	DamageStatusLabel->visible = 1;

	SpeedStatusLabel = new Label(GAME->HudMan);
	SpeedStatusLabel->posx = 100;
	SpeedStatusLabel->posy = 72;
	SpeedStatusLabel->width = 300;
	SpeedStatusLabel->height = 16;
	SpeedStatusLabel->visible = 1;

	ExplosionRadiusStatusLabel = new Label(GAME->HudMan);
	ExplosionRadiusStatusLabel->posx = 100;
	ExplosionRadiusStatusLabel->posy = 88;
	ExplosionRadiusStatusLabel->width = 300;
	ExplosionRadiusStatusLabel->height = 16;
	ExplosionRadiusStatusLabel->visible = 1;

	RangeStatusLabel = new Label(GAME->HudMan);
	RangeStatusLabel->posx = 100;
	RangeStatusLabel->posy = 104;
	RangeStatusLabel->width = 300;
	RangeStatusLabel->height = 16;
	RangeStatusLabel->visible = 1;

	MaxHealthStatusLabel = new Label(GAME->HudMan);
	MaxHealthStatusLabel->posx = 100;
	MaxHealthStatusLabel->posy = 120;
	MaxHealthStatusLabel->width = 300;
	MaxHealthStatusLabel->height = 16;
	MaxHealthStatusLabel->visible = 1;

	MaxArmorStatusLabel = new Label(GAME->HudMan);
	MaxArmorStatusLabel->posx = 100;
	MaxArmorStatusLabel->posy = 136;
	MaxArmorStatusLabel->width = 300;
	MaxArmorStatusLabel->height = 16;
	MaxArmorStatusLabel->visible = 1;

	HealthStatusLabel = new Label(GAME->HudMan);
	HealthStatusLabel->posx = 100;
	HealthStatusLabel->posy = 152;
	HealthStatusLabel->width = 300;
	HealthStatusLabel->height = 16;
	HealthStatusLabel->visible = 1;

	ArmorStatusLabel = new Label(GAME->HudMan);
	ArmorStatusLabel->posx = 100;
	ArmorStatusLabel->posy = 168;
	ArmorStatusLabel->width = 300;
	ArmorStatusLabel->height = 16;
	ArmorStatusLabel->visible = 1;

	CriticalStrikeChanceStatusLabel = new Label(GAME->HudMan);
	CriticalStrikeChanceStatusLabel->posx = 100;
	CriticalStrikeChanceStatusLabel->posy = 184;
	CriticalStrikeChanceStatusLabel->width = 300;
	CriticalStrikeChanceStatusLabel->height = 16;
	CriticalStrikeChanceStatusLabel->visible = 1;

	CriticalStrikeMultiplierStatusLabel = new Label(GAME->HudMan);
	CriticalStrikeMultiplierStatusLabel->posx = 100;
	CriticalStrikeMultiplierStatusLabel->posy = 200;
	CriticalStrikeMultiplierStatusLabel->width = 300;
	CriticalStrikeMultiplierStatusLabel->height = 16;
	CriticalStrikeMultiplierStatusLabel->visible = 1;

	SizeStatusLabel = new Label(GAME->HudMan);
	SizeStatusLabel->posx = 100;
	SizeStatusLabel->posy = 216;
	SizeStatusLabel->width = 300;
	SizeStatusLabel->height = 16;
	SizeStatusLabel->visible = 1;

	InvisibilityStatusLabel = new Label(GAME->HudMan);
	InvisibilityStatusLabel->posx = 100;
	InvisibilityStatusLabel->posy = 232;
	InvisibilityStatusLabel->width = 300;
	InvisibilityStatusLabel->height = 16;
	InvisibilityStatusLabel->visible = 1;

	GodModeStatusLabel = new Label(GAME->HudMan);
	GodModeStatusLabel->posx = 100;
	GodModeStatusLabel->posy = 248;
	GodModeStatusLabel->width = 300;
	GodModeStatusLabel->height = 16;
	GodModeStatusLabel->visible = 1;

	ScoreStatusLabel = new Label(GAME->HudMan);
	ScoreStatusLabel->posx = 100;
	ScoreStatusLabel->posy = 264;
	ScoreStatusLabel->width = 300;
	ScoreStatusLabel->height = 16;
	ScoreStatusLabel->visible = 1;

	RespawnDelayStatusLabel = new Label(GAME->HudMan);
	RespawnDelayStatusLabel->posx = 100;
	RespawnDelayStatusLabel->posy = 280;
	RespawnDelayStatusLabel->width = 300;
	RespawnDelayStatusLabel->height = 16;
	RespawnDelayStatusLabel->visible = 1;

	AmmunitionStatusLabel = new Label(GAME->HudMan);
	AmmunitionStatusLabel->posx = 100;
	AmmunitionStatusLabel->posy = 296;
	AmmunitionStatusLabel->width = 300;
	AmmunitionStatusLabel->height = 16;
	AmmunitionStatusLabel->visible = 1;

}

GameHUD::~GameHUD(void)
{
	delete FanOutStatusLabel;
	delete ShootDelayStatusLabel;
	delete DamageStatusLabel;
	delete SpeedStatusLabel;
	delete ExplosionRadiusStatusLabel;
	delete RangeStatusLabel;
	delete MaxHealthStatusLabel;
	delete MaxArmorStatusLabel;
	delete HealthStatusLabel;
	delete ArmorStatusLabel;
	delete CriticalStrikeChanceStatusLabel;
	delete CriticalStrikeMultiplierStatusLabel;
	delete SizeStatusLabel;
	delete InvisibilityStatusLabel;
	delete GodModeStatusLabel;
	delete ScoreStatusLabel;
	delete RespawnDelayStatusLabel;
	delete AmmunitionStatusLabel;
}

void GameHUD::UpdatePowerUpsStatusLabels(void)
{
	char Data[1024];

#define SetText(x)		{\
							if (x->text == NULL)\
							{\
								free(x->text);\
							}\
							x->text = strdup(Data);\
							x->textLength = strlen(x->text);\
						}

	sprintf(Data,"Fan Out Level %d : shooting %d shells.",GAME->Player->PowerUps.FanOutLevel,FanOutValues[GAME->Player->PowerUps.FanOutLevel]);
	SetText(FanOutStatusLabel);

	sprintf(Data,"Shooting Delay Level %d : shoot every %.3f seconds.",GAME->Player->PowerUps.ShootDelayLevel,ShootDelayValues[GAME->Player->PowerUps.ShootDelayLevel]);
	SetText(ShootDelayStatusLabel);

	sprintf(Data,"Damage Level %d : damage increased by %.3f %%.",GAME->Player->PowerUps.DamageLevel,DamageValues[GAME->Player->PowerUps.DamageLevel]);
	SetText(DamageStatusLabel);

	sprintf(Data,"Speed Level %d : movement speed increased by %.3f %%.",GAME->Player->PowerUps.SpeedLevel,SpeedValues[GAME->Player->PowerUps.SpeedLevel]);
	SetText(SpeedStatusLabel);

	sprintf(Data,"Explosion Radius Level %d : impact damage radius increased by %.3f %%.",GAME->Player->PowerUps.ExplosionRadiusLevel,ExplosionRadiusValues[GAME->Player->PowerUps.ExplosionRadiusLevel]);
	SetText(ExplosionRadiusStatusLabel);

	sprintf(Data,"Range Level %d : shooting range increased by %.3f %%.",GAME->Player->PowerUps.RangeLevel,RangeValues[GAME->Player->PowerUps.RangeLevel]);
	SetText(RangeStatusLabel);

	sprintf(Data,"Max Health %d.",GAME->Player->PowerUps.MaxHealth);
	SetText(MaxHealthStatusLabel);

	sprintf(Data,"Max Armor %d.",GAME->Player->PowerUps.MaxArmor);
	SetText(MaxArmorStatusLabel);

	sprintf(Data,"Current Health %d.",GAME->Player->PowerUps.Health);
	SetText(HealthStatusLabel);

	sprintf(Data,"Current Armor %d.",GAME->Player->PowerUps.Armor);
	SetText(ArmorStatusLabel);

	sprintf(Data,"Critical Strike Chance Level %d : chance of critical strike is %.3f %%.",GAME->Player->PowerUps.CriticalStrikeChanceLevel,CriticalStrikeChanceValues[GAME->Player->PowerUps.CriticalStrikeChanceLevel]);
	SetText(CriticalStrikeChanceStatusLabel);

	sprintf(Data,"Critical Strike Multiplier Level %d : a critical hit does %.3f %% more damage.",GAME->Player->PowerUps.CriticalStrikeMultiplierLevel,CriticalStrikeMultiplierValues[GAME->Player->PowerUps.CriticalStrikeMultiplierLevel]);
	SetText(CriticalStrikeMultiplierStatusLabel);

	sprintf(Data,"Tank Size Level %d : tank's size is smaller by %.3f %%.",GAME->Player->PowerUps.SizeLevel,SizeValues[GAME->Player->PowerUps.SizeLevel]);
	SetText(SizeStatusLabel);

	sprintf(Data,"Invisible Level %d : tank's visibility is reduced by %.3f %%.",GAME->Player->PowerUps.InvisibilityLevel,InvisibilityLevel[GAME->Player->PowerUps.InvisibilityLevel]);
	SetText(InvisibilityStatusLabel);

	sprintf(Data,"God Mode status remaining time %d.",GAME->Player->PowerUps.GodModeRemainingTime);
	SetText(GodModeStatusLabel);

	sprintf(Data,"Score %d.",GAME->Player->PowerUps.Score);
	SetText(ScoreStatusLabel);

	sprintf(Data,"Respawn delay is reduced by %d seconds.",GAME->Player->PowerUps.RespawnDelay);
	SetText(RespawnDelayStatusLabel);

	sprintf(Data,"Ammunition count %d.",0);
	SetText(AmmunitionStatusLabel);

#undef SetText
}
