
#include "TankIncludes.h"

Tank::Tank(void) : BaseObject()
{
	type = otTank;
}

Tank::~Tank(void)
{
}

void Tank::Update(void)
{

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

	mat.m11 = planex.x;
	mat.m21 = planex.y;
	mat.m31 = planex.z;

	mat.m12 = planey.x;
	mat.m22 = planey.y;
	mat.m32 = planey.z;

	mat.m13 = planez.x;
	mat.m23 = planez.y;
	mat.m33 = planez.z;


	//TODO actulizeaza inaltimea sa fie corecta

	//pos.y = GAME->GetTerrain()->ComputeHeight(pos.x,pos.z);

	//pos.y = (((pos1.y + pos2.y) / 2) + pos3.y) / 2;

	mat.Translation() = pos;
}

void Tank::Render(void)
{

/*	Matrix mat2;
	Matrix::CreateFromQuaternion(&orient,&mat2);

	Vector3 off,cen,dx,dy,dz;
	dx.Set(model->BoundBox.offset.x,0,0);
	dy.Set(0,model->BoundBox.offset.y,0);
	dz.Set(0,0,model->BoundBox.offset.z);

	mat2.Transpose();

	dx = mat2 * dx;
	dy = mat2 * dy;
	dz = mat2 * dz;
	off = (mat2 * model->BoundBox.offset) + pos - dy * 2;
	cen = (mat2 * model->BoundBox.center) + pos;

	Vector3 pos1 = off;
	Vector3 pos2 = off - dx * 2;
	Vector3 pos3 = off - dx - dz * 2;

	pos1.y = GAME->GetTerrain()->ComputeHeight(pos1.x,pos1.z) + 0.1;
	pos2.y = GAME->GetTerrain()->ComputeHeight(pos2.x,pos2.z) + 0.1;
	pos3.y = GAME->GetTerrain()->ComputeHeight(pos3.x,pos3.z) + 0.1;

	Vector3 planex = pos1 - pos2;
	Vector3 planez = ((pos1 + pos2) / 2) - pos3;
	Vector3 planey;

	planex.Normalize();
	planez.Normalize();
	Vector3::Cross(&planez,&planex,&planey);
	planey.Normalize();
	Vector3::Cross(&planey,&planez,&planex);
	planex.Normalize();					  

	mat2.m11 = planex.x;
	mat2.m21 = planex.y;
	mat2.m31 = planex.z;

	mat2.m12 = planey.x;
	mat2.m22 = planey.y;
	mat2.m32 = planey.z;

	mat2.m13 = planez.x;
	mat2.m23 = planez.y;
	mat2.m33 = planez.z;

	VertexPosColor Buff[3];
	Buff[0].pos = pos1;
	Buff[0].color.Set(255,0,0,255);
	Buff[1].pos = pos2;
	Buff[1].color.Set(0,255,0,255);
	Buff[2].pos = pos3;
	Buff[2].color.Set(0,0,255,255);

	unsigned short Index[3] = {2,1,0};

	mat2 = Matrix::Identity;
	GAME->GameRenderer->SetModel(&mat2);
	GAME->GameRenderer->DrawBuffer(GL_TRIANGLE_STRIP,Buff,Index,3);*/

	Matrix mat2 = mat;
	mat2.Translation().Set(0.0,0.0,0.0);
	mat2.Transpose();
	mat2.Translation() = mat.Translation();
//	mat.Transpose();

	model->Draw(GAME->GameRenderer,&mat);
}

void Tank::RenderBoundingBox(void)
{
	model->DrawBoundingBox(GAME->GameRenderer,&mat);
}
