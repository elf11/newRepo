
#include "TankIncludes.h"

PlayerInput::PlayerInput(void)
{
}

PlayerInput::~PlayerInput(void)
{

}

void PlayerInput::OnMouseDown(int x, int y)
{
}

void PlayerInput::OnMouseUp(int x, int y)
{
}

void PlayerInput::OnMouseMove(int x, int y)
{
	float pitch = GAME->PlayerCamera->ObjectFollowPitch;
	if (Owner->MouseDown > 0)
	{
		pitch -= ((float)(Owner->DeltaMY)) / 300;
		pitch = Math::Clamp(pitch, -Math::PiOver2 + 0.0005f, Math::PiOver2 - 0.0005f);

		Owner->DeltaMY = 0;
	}

	GAME->PlayerCamera->ObjectFollowPitch = pitch;

	float yaw = 0.0;
	if (Owner->MouseDown > 0)
	{
		yaw -= ((float)(Owner->DeltaMX)) / 300;

		Owner->DeltaMX = 0;
	}
	GAME->Player->yawdiff = yaw;


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

void PlayerInput::OnKeyDown(int key)
{
}

void PlayerInput::OnKeyUp(int key)
{
}

void PlayerInput::OnFrame(void)
{
	Vector3 &pos = GAME->Player->object->pos;
	Quaternion &orient = GAME->Player->object->orient;

	orient.RotateY(GAME->Player->yawdiff);
	GAME->Player->yawdiff = 0.0;

	Vector3 dir = orient.Forward();
	dir.y = 0;
	dir.Normalize();

	Vector3 accel;
	accel.Set(0.0,-9.8,0.0);
	accel += -GAME->Player->speed;
	if ((GAME->HudMan->KeyState['W'] > 0) && (Owner->FocusedElement == NULL))
	{
		accel += orient.Forward() * 1000.0;
	}
	if ((GAME->HudMan->KeyState['S'] > 0) && (Owner->FocusedElement == NULL))
	{
		accel -= orient.Forward() * 1000.0;
	}

	pos += (GAME->Player->speed * GAME->DeltaFrameTime) +
		   (accel * GAME->DeltaFrameTime * GAME->DeltaFrameTime / 2);
	GAME->Player->speed += (accel * GAME->DeltaFrameTime);

	pos.y = Math::Min(pos.y,GAME->GetTerrain()->ComputeHeight(pos.x,pos.z));

	if (GAME->Player->weap != NULL)
	{
		if ((Owner->KeyState[' '] > 0) && (Owner->FocusedElement == NULL))
		{
			Matrix mat;
			Model *model = GAME->Player->object->model;

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

			if (GAME->Player->weap->Fire(FirePos,FireDir * 4000.0))
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
					P->data.speed += GAME->Player->speed;
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
}
