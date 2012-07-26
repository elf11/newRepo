
#ifndef GAMEPLAYER__H
#define GAMEPLAYER__H

#include "TankIncludes.h"

class Model;
class Weapon;
class BaseObject;

class GamePlayer
{
public :
	enum
	{
		GAMEPLAYER_MAIN,
		GAMEPLAYER_AI,
		GAMEPLAYER_NETWORK,
	};
	int type;
	BaseObject* object;

	PowerUpPlayerStatus PowerUps;

	Weapon *weap;
	Quaternion weaporient;

	char *name;

	Vector3 speed;

	float yawdiff;



	int AIhastarget;
	Vector3 AItargetpos;
	void MoveTank(Vector3 start, Vector3 finish, int speed); 
	double GetDistance(Vector3 source, Vector3 dest);

	GamePlayer(void);

	void SetControlledObject(BaseObject* obj);

	void UpdateMyControls(void);
	virtual void Update(void);

};

class PlayerManager
{
public :
	PlayerManager(void);
	Array<GamePlayer *> players;

	GamePlayer *GetPlayer(char *Name);

	void AddPlayer(GamePlayer *Player);
	void RemovePlayer(char *Name);
};

#endif
