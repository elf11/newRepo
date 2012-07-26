
#include "TankIncludes.h"

Camera::Camera(void)
{
	windowx = 1024;
	windowy = 768;
	pos.Set(0,0,0);
	type = CAMERA_FREE;
	followObject = NULL;
	ObjectFollowPitch = 0.0;
}

Camera::~Camera(void)
{

}

void Camera::UpdateWindowData(int wx,int wy)
{
	windowx = wx;
	windowy = wy;
}

void Camera::CopyCameraMat(Matrix &To)
{
	To = CameraMat;
}

void Camera::Update(void)
{
	UpdateWindowData(GAME->WindowWidth,GAME->WindowHeight);
	
	Matrix::CreatePerspective(Math::PiOver4,((float)(windowx)) / windowy, 1.0f, 40000.f, &PerspectiveMat);

	UpdateOrient();
	UpdatePosition();
}

void Camera::Render(void)
{
	Vector3 temppos = -pos;
	Matrix TranslateMat = Matrix::Identity;
	TranslateMat.Translate(temppos);

	Matrix::CreateFromQuaternion(&orient,&CameraMat);
	CameraMat.Transpose();

	CameraMat = CameraMat * TranslateMat;

	GAME->GameRenderer->SetPerspective(&PerspectiveMat);
	GAME->GameRenderer->SetCamera(&CameraMat);
}

void Camera::UpdatePosition()
{
	switch(type)
	{
		case CAMERA_3RDPERSON:
		   {
			   if (!followObject)
				   return;
			   pos = followObject->pos;
			   pos -= orient.Forward() * 100;

			   float ty = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);
			   ty += 10.0f;
			   if (pos.y < ty)
			   {
				   pos.y = ty;
			   }
		   }
		   break;
	   case CAMERA_FREE:



		   break;
	   }

	

}

void Camera::UpdateOrient()
{
	switch(type)
	{
	case CAMERA_3RDPERSON:
		{
			if (!followObject)
				return;
			 orient = followObject->orient;
			 orient.RotateX(ObjectFollowPitch);
		}
		break;
	case CAMERA_FREE:
		break;
	}
}

void Camera::Change( int newtype, BaseObject* follow )
{
	type = newtype;

	if(newtype == CAMERA_3RDPERSON)
		followObject =follow;

	if (newtype == CAMERA_FREE)
		followObject = NULL;

}
