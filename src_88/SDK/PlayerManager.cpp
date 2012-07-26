
#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"
#include "FileLoader.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "PlayerManager.h"
#include "GamePlayer.h"

PlayerManager :: PlayerManager(void)
{

}

GamePlayer PlayerManager::GetPlayer(int type)
{
	return GamePlayer.type;
}

Array<GamePlayer *> PlayerManager ::AddPlayer(GamePlayer Player)
{
	for(int i = 0; i < players.Length(); i++)
	{
		if(strcmp(Player.type, players[i].type) != 0)
		{
			players.Push(Player);
		}
	}

	return NULL;
}


Array<GamePlayer *> PlayerManager ::RemovePlayer(GamePlayer Player)
{
	for(int i = 0; i < players.Length(); i++)
	{
		if(strcmp(Player.type, players[i].type) != 0)
		{
			players.Remove(Player);
		}
	}

	return NULL;
}