
#include "TankIncludes.h"

GamePlayer::GamePlayer(void)
{
	object = NULL;
	type = GAMEPLAYER_MAIN;
	AItargetpos.Set(0,0,0);
	AIhastarget = 0;
	weap = NULL;
	weaporient = Quaternion::Identity;
	speed.Set(0.0,0.0,0.0);
	yawdiff = 0.0;
}

void GamePlayer::SetControlledObject(BaseObject* obj)
{
	Tank *tnk = ((Tank *)(object));
	if (tnk != NULL)
	{
		if (tnk->Owner == this)
		{
			tnk->Owner = NULL;
		}
	}
	tnk = ((Tank *)(obj));
	tnk->Owner = this;
	object = obj;
}

void GamePlayer::UpdateMyControls(void)
{
/*	if (!object)
	{
		return;
	}

	Vector3 &pos = object->pos;
	Quaternion &orient = object->orient;

	Vector3 dir = orient.Forward();


	dir.y = 0;

	dir.Normalize();

	Vector3 accel;
	accel.Set(0.0,-9.8,0.0);
	accel += -speed;
	if (KeyState['W'] > 0)
	{
		accel += object->orient.Forward() * 400.0;
	}
	if (KeyState['S'] > 0)
	{
		accel -= object->orient.Forward() * 400.0;
	}

	pos = pos + ((speed * GAME->DeltaFrameTime) + (accel * GAME->DeltaFrameTime * GAME->DeltaFrameTime / 2));
	speed = speed + (accel * GAME->DeltaFrameTime);

	pos.y = Math::Min(pos.y,GAME->GetTerrain()->ComputeHeight(pos.x,pos.z));

	if ((type == GAMEPLAYER_MAIN) && (weap != NULL))
	{
		if (KeyState[' '] > 0)
		{
			Matrix mat;
			Model *model = object->model;

			Matrix::CreateFromQuaternion(&orient,&mat);

			Vector3 off,cen,dx,dy,dz;
			dx.Set(model->BoundBox.offset.x,0,0);
			dy.Set(0,model->BoundBox.offset.y,0);
			dz.Set(0,0,model->BoundBox.offset.z);

			mat.Transpose();

			dx = mat * dx;
			dy = mat * dy;
			dz = mat * dz;
			off = (mat * model->BoundBox.offset) + pos - dy * 2;
			cen = (mat * model->BoundBox.center) + pos;

			Vector3 pos1 = off;
			Vector3 pos2 = off - dx * 2;
			Vector3 pos3 = off - dx - dz * 2;

			pos1.y = GAME->GetTerrain()->ComputeHeight(pos1.x,pos1.z);
			pos2.y = GAME->GetTerrain()->ComputeHeight(pos2.x,pos2.z);
			pos3.y = GAME->GetTerrain()->ComputeHeight(pos3.x,pos3.z);

			Vector3 planex = pos1 - pos2;
			Vector3 planez = ((pos1 + pos2) / 2) - pos3;
			Vector3 planey;

			planex.Normalize();
			planez.Normalize();
			Vector3::Cross(&planez,&planex,&planey);
			planey.Normalize();
			Vector3::Cross(&planey,&planez,&planex);
			planex.Normalize();

			mat = Matrix::Identity;
			mat.m11 = planex.x;
			mat.m21 = planex.y;
			mat.m31 = planex.z;

			mat.m12 = planey.x;
			mat.m22 = planey.y;
			mat.m32 = planey.z;

			mat.m13 = planez.x;
			mat.m23 = planez.y;
			mat.m33 = planez.z;

			Vector3 FireDir = -planez;

			Matrix RotX = Matrix::Identity;
			RotX.Rotate(planex,Math::PiOver6 / 64.0);
			FireDir = RotX * FireDir;
			FireDir.Normalize();

			mat.Transpose();

			dy = mat * dy;

			Vector3 FirePos;
			FirePos.Set(pos.x,GAME->GetTerrain()->ComputeHeight(pos.x,pos.z),pos.z);
			FirePos = FirePos - dz + dy;

			if (weap->Fire(FirePos,FireDir * 4000.0))
			{
				Vector3 Wind;
				Wind.Set(rand() % 50 - 25,rand() % 50,rand() % 50 - 25);
				for (int i = 0;i < 100;i += 1)
				{
					LinkedNode<Particle> *P = new LinkedNode<Particle>();
					P->data.Height = 2.0;
					P->data.Width = 2.0;
					P->data.pos = FirePos;
					P->data.speed.Set(FireDir.x * 100 + rand() % 30 - 15,
						              FireDir.y * 100 + rand() % 30 - 15,
									  FireDir.z * 100 + rand() % 30 - 15);
					P->data.speed = P->data.speed / (rand() % 5);
					P->data.speed += speed;
					P->data.accel = Wind;
					P->data.accel.y *= 2;
					P->data.ToLive = ((float)(rand() % 7000)) / 700;
					P->data.col.Set(rand() % 256,rand() % 256,rand() % 256,255);
					GAME->PtcMan->particles.AppendRight(P);
				}
			}

		}
	}

	float turn = 0.0;
	if (KeyState['D'] > 0)
	{
		turn += 1.0;
	}
	if (KeyState['A'] > 0)
	{
		turn -= 1.0;
	}

	float yaw = orient.Yaw();

	float ty = speed.y;
	speed.y = 0;
	float val = speed.Length();//Vector3::Dot(&speed,&object->orient.Forward());
	speed.y = ty;
	val /= 50;

	yaw -= ((float)(turn * val * Math::Sign0(val))) / 100;

	Quaternion::CreateRotationY(yaw,&orient);

	pos.y = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);

	if (MouseRightDown > 0)
	{
		float yaw = weaporient.Yaw();
		yaw -= ((float)(DeltaMX)) / 300;

		Quaternion::CreateRotationY(yaw,&weaporient);

	}

	if (MouseDown > 0)
	{
		float yaw = orient.Yaw();
		yaw -= ((float)(DeltaMX)) / 300;

		Quaternion::CreateRotationY(yaw,&orient);

		DeltaMX = 0;
	}*/
}


double GamePlayer::GetDistance(Vector3 source, Vector3 dest)
{
	double tempSource, tempDest, distance;

	tempSource = source.x - dest.x;
	tempSource = Math::Pow(tempSource, 2.0);
	tempDest = source.z - dest.z;
	tempDest = Math::Pow(tempDest, 2.0);
	
	distance = tempSource + tempDest;

	return Math::Sqrt(distance);
}

void GamePlayer::MoveTank(Vector3 source, Vector3 dest, int speed)
{
	source.y = GAME->GetTerrain()->ComputeHeight(source.x,source.z);
	dest.y = GAME->GetTerrain()->ComputeHeight(dest.x,dest.z);

	Vector3 vec = dest - source;
	vec.Normalize();
	vec = vec * speed * GAME->DeltaFrameTime;

	if ((source - dest).Length() < vec.Length())
	{
		vec *= (source - dest).Length() / vec.Length();
	}

	object->pos += vec;
}

void GamePlayer::Update(void)
{
/*	if (type == GAMEPLAYER_MAIN)
	{
		Vector3 &pos = object->pos;
		Quaternion &orient = object->orient;

		Vector3 dir = orient.Forward();
		dir.y = 0;
		dir.Normalize();

		Vector3 accel;
		accel.Set(0.0,-9.8,0.0);
		accel += -speed;
		if (GAME->HudMan->KeyState['W'] > 0)
		{
			accel += object->orient.Forward() * 400.0;
		}
		if (GAME->HudMan->KeyState['S'] > 0)
		{
			accel -= object->orient.Forward() * 400.0;
		}

		pos = pos + ((speed * GAME->DeltaFrameTime) + (accel * GAME->DeltaFrameTime * GAME->DeltaFrameTime / 2));
		speed = speed + (accel * GAME->DeltaFrameTime);

		pos.y = Math::Min(pos.y,GAME->GetTerrain()->ComputeHeight(pos.x,pos.z));

		if ((type == GAMEPLAYER_MAIN) && (weap != NULL))
		{
			if (GAME->HudMan->KeyState[' '] > 0)
			{
				Matrix mat;
				Model *model = object->model;

				Matrix::CreateFromQuaternion(&orient,&mat);

				Vector3 off,cen,dx,dy,dz;
				dx.Set(model->BoundBox.offset.x,0,0);
				dy.Set(0,model->BoundBox.offset.y,0);
				dz.Set(0,0,model->BoundBox.offset.z);

				mat.Transpose();

				dx = mat * dx;
				dy = mat * dy;
				dz = mat * dz;
				off = (mat * model->BoundBox.offset) + pos - dy * 2;
				cen = (mat * model->BoundBox.center) + pos;

				Vector3 pos1 = off;
				Vector3 pos2 = off - dx * 2;
				Vector3 pos3 = off - dx - dz * 2;

				pos1.y = GAME->GetTerrain()->ComputeHeight(pos1.x,pos1.z);
				pos2.y = GAME->GetTerrain()->ComputeHeight(pos2.x,pos2.z);
				pos3.y = GAME->GetTerrain()->ComputeHeight(pos3.x,pos3.z);

				Vector3 planex = pos1 - pos2;
				Vector3 planez = ((pos1 + pos2) / 2) - pos3;
				Vector3 planey;

				planex.Normalize();
				planez.Normalize();
				Vector3::Cross(&planez,&planex,&planey);
				planey.Normalize();
				Vector3::Cross(&planey,&planez,&planex);
				planex.Normalize();

				mat = Matrix::Identity;
				mat.m11 = planex.x;
				mat.m21 = planex.y;
				mat.m31 = planex.z;

				mat.m12 = planey.x;
				mat.m22 = planey.y;
				mat.m32 = planey.z;

				mat.m13 = planez.x;
				mat.m23 = planez.y;
				mat.m33 = planez.z;

				Vector3 FireDir = -planez;

				Matrix RotX = Matrix::Identity;
				RotX.Rotate(planex,Math::PiOver6 / 64.0);
				FireDir = RotX * FireDir;
				FireDir.Normalize();

				mat.Transpose();

				dy = mat * dy;

				Vector3 FirePos;
				FirePos.Set(pos.x,GAME->GetTerrain()->ComputeHeight(pos.x,pos.z),pos.z);
				FirePos = FirePos - dz + dy;

				if (weap->Fire(FirePos,FireDir * 4000.0))
				{
					Vector3 Wind;
					Wind.Set(rand() % 50 - 25,rand() % 50,rand() % 50 - 25);
					for (int i = 0;i < 100;i += 1)
					{
						LinkedNode<Particle> *P = new LinkedNode<Particle>();
						P->data.Height = 2.0;
						P->data.Width = 2.0;
						P->data.pos = FirePos;
						P->data.speed.Set(FireDir.x * 100 + rand() % 30 - 15,
							FireDir.y * 100 + rand() % 30 - 15,
							FireDir.z * 100 + rand() % 30 - 15);
						P->data.speed = P->data.speed / (rand() % 5);
						P->data.speed += speed;
						P->data.accel = Wind;
						P->data.accel.y *= 2;
						P->data.ToLive = ((float)(rand() % 7000)) / 700;
						P->data.col.Set(rand() % 256,rand() % 256,rand() % 256,255);
						GAME->PtcMan->particles.AppendRight(P);
					}
				}

			}
		}

		pos.y = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);

		return;
	}*/

	if(type == GAMEPLAYER_AI)
	{
		Vector3 &tankPos = object->pos;
		Quaternion &orient = object->orient;

		while (((Math::Abs(tankPos.x - AItargetpos.x) < 0.1) && (Math::Abs(tankPos.z - AItargetpos.z) < 0.1)) || (AIhastarget == 0))
		{
			float posx = (float)(rand()) / 32768;
			float posz = (float)(rand()) / 32768;
			posx *= 0.8;
			posx += 0.1;
			posz *= 0.8;
			posz += 0.1;
			posx *= ((GAME->GetTerrain())->GetTerrainModel()->MapWidth * GAME->GetTerrain()->WidthRatio);
			posz *= ((GAME->GetTerrain())->GetTerrainModel()->MapHeight * GAME->GetTerrain()->HeightRatio);
			AItargetpos.Set(posx,0,posz);
			AIhastarget = 1;
		}

		Quaternion::CreateFromYawPitchRoll(Math::Atan2(tankPos.x - AItargetpos.x,tankPos.z - AItargetpos.z),0,0,&orient);
		MoveTank(tankPos,AItargetpos,50);
		tankPos.y = GAME->GetTerrain()->ComputeHeight(tankPos.x,tankPos.z);
	}

}

PlayerManager::PlayerManager(void)
{

}

GamePlayer * PlayerManager::GetPlayer(char *Name)
{
	for (int i = 0;i < players.Length();i += 1)
	{
		if (strcmp(Name,players[i]->name) == 0)
		{
			return players[i];
		}
	}
	return NULL;
}

void PlayerManager::AddPlayer(GamePlayer *Player)
{
	players.Push(Player);
}

void PlayerManager::RemovePlayer(char *Name)
{
	for (int i = 0;i < players.Length();i += 1)
	{
		if (strcmp(Name,players[i]->name) == 0)
		{
			players.RemoveNo(i);
			return;
		}
	}
}

//void GamePlayer::Update(void)
//{

/*	if (MouseDown > 0)
	{
		float yaw = orient.Yaw();
		float pitch = orient.Pitch();

		yaw -= ((float)(DeltaMX)) / 300;
		pitch -= ((float)(DeltaMY)) / 300;
		pitch = Math::Clamp(pitch, -Math::PiOver2 + 0.005f, Math::PiOver2 - 0.005f);
		Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0, &orient);
		DeltaMX = 0;
		DeltaMY = 0;
	}

	if (KeyState['U'] > 0)
	{
		pos.z += GAME->DeltaFrameTime * 3;
	}
	if (KeyState['J'] > 0)
	{
		pos.z -= GAME->DeltaFrameTime * 3;
	}

	if (KeyState['K'] > 0)
	{
		pos.x += GAME->DeltaFrameTime * 3;
	}
	if (KeyState['H'] > 0)
	{
		pos.x -= GAME->DeltaFrameTime * 3;
	}

	if (KeyState['O'] > 0)
	{
		pos.y += GAME->DeltaFrameTime * 3;
	}
	if (KeyState['L'] > 0)
	{
		pos.y -= GAME->DeltaFrameTime * 3;
	}

	if (KeyState['R'] > 0)
	{
		pos += orient.UpDir();
	}
	if (KeyState['F'] > 0)
	{
		pos -= orient.UpDir();
	}*/

/*!!!!!!!

	if (KeyState['W'] > 0)
	{
		pos += orient.Forward();
	}
	if (KeyState['S'] > 0)
	{
		pos -= orient.Forward();
	}

	if (KeyState['D'] > 0)
	{
		pos += orient.RightDir();
	}
	if (KeyState['A'] > 0)
	{
		pos -= orient.RightDir();
	}

	pos.y = GAME->Terrain->modeldata->ComputeHeight(pos.x,pos.z);

	if (MouseDown == 0)
	{
		DeltaMX = 0;
		DeltaMY = 0;
	}

	Vector3 normalvec;
	GAME->Terrain->modeldata->ComputeNormal(pos.x,pos.z,normalvec);

	float yaw = orient.Yaw();
	yaw -= ((float)(DeltaMX)) / 300;

	Quaternion::CreateFromAxisAngle(&normalvec,yaw,&orient);
	DeltaMX = 0;
	DeltaMY = 0;


	/*
	if (object)
	{
		object->pos = pos;
		object->orient = orient;
	}
	*/
//}
/*
void GamePlayer::Render(void)
{
	Matrix TankMat;
	TankMat.CreateFromQuaternion(&orient,&TankMat);
	TankMat.Translate(pos);

	model->Draw(GAME->GameRenderer,&TankMat);

}

void GamePlayer::SetControlledObject( BaseObject* obj )
{
	  object = obj;
}
*/