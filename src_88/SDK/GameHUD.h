
#ifndef GAMEHUD__H
#define GAMEHUD__H

class GameHUD
{
public :
	Label *FanOutStatusLabel;
	Label *ShootDelayStatusLabel;
	Label *DamageStatusLabel;
	Label *SpeedStatusLabel;
	Label *ExplosionRadiusStatusLabel;
	Label *RangeStatusLabel;
	Label *MaxHealthStatusLabel;
	Label *MaxArmorStatusLabel;
	Label *HealthStatusLabel;
	Label *ArmorStatusLabel;
	Label *CriticalStrikeChanceStatusLabel;
	Label *CriticalStrikeMultiplierStatusLabel;
	Label *SizeStatusLabel;
	Label *InvisibilityStatusLabel;
	Label *GodModeStatusLabel;
	Label *ScoreStatusLabel;
	Label *RespawnDelayStatusLabel;
	Label *AmmunitionStatusLabel;

	GameHUD(void);
	~GameHUD(void);

	void UpdatePowerUpsStatusLabels(void);
};

#endif

