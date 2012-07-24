
#include "Camera.h"

Camera::Camera(void)
{
	windowx = 1024;
	windowy = 768;
	pos.Set(0,2,5);
}

void Camera::UpdateWindowData(int wx,int wy)
{
	windowx = wx;
	windowy = wy;
}

void Camera::Update(void)
{
	Matrix::CreatePerspective(Math::PiOver4,((float)(windowx)) / windowy, 0.1f, 1000.f, &PerspectiveMat);

	if (MouseDown > 0)
	{
		float yaw = orient.Yaw();
		float pitch = orient.Pitch();

		yaw -= ((float)(DeltaMX)) / 300;
		pitch -= ((float)(DeltaMY)) / 300;
		pitch = Math::Clamp(pitch, -Math::PiOver2 + 0.005f, Math::PiOver2 - 0.005f);
		Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0, &orient);
		DeltaMX = 0;
		DeltaMY = 0;
/*

		Vector3 axis;

		axis.Set(0.0,1.0,0.0);
		orient.Rotate(&axis,);
		DeltaMX = 0;

		axis = orient.RightDir();
		axis.y = 0;
		axis.Normalize();
		orient.Rotate(&axis,((float)(DeltaMY)) / 300);
		DeltaMY = 0;	*/
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

	if (KeyState['R'] > 0)
	{
		pos += orient.UpDir();
	}
	if (KeyState['F'] > 0)
	{
		pos -= orient.UpDir();
	}
}

void Camera::Render(void)
{
	Matrix::CreateFromQuaternion(&orient,&CameraMat);
	CameraMat.Transpose();

	Vector3 temppos = -pos;
	CameraMat.Translate(temppos);

	GAME->GameRenderer->SetPerspective(&PerspectiveMat);
	GAME->GameRenderer->SetCamera(&CameraMat);
}
