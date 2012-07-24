
#include "Camera.h"

Camera::Camera(void)
{
	windowx = 1024;
	windowy = 768;
	pos.Set(0,6,-5);
}

void Camera::UpdateWindowData(int wx,int wy)
{
 windowx = wx;
 windowy = wy;
}

void Camera::Update(void)
{
	PerspectiveMat = Matrix::CreatePerspective(Math::PiOver2,((float)(windowx)) / windowy,0.01,1000.0);
	Matrix::CreatePerspective(Math::PiOver3, 1024.f/768.f, 0.0001f, 1000.f, &PerspectiveMat);
}

void Camera::Render(void)
{
	Matrix::CreateFromQuaternion(&orient,&CameraMat);
	pos.Set(0, 0, -3);
	CameraMat.Translate(pos);
	Matrix::CreateTranslation(&pos, &CameraMat);
	CameraMat = Matrix::Identity;
	GAME->GameRenderer->SetPerspective(&PerspectiveMat);
	GAME->GameRenderer->SetCamera(&CameraMat);
}
