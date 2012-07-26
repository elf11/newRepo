
#include "TankIncludes.h"

Building::Building(void)
{
	type = otBuilding;
}

Building::~Building(void)
{

}

void Building::Update(void)
{
	Matrix::CreateFromQuaternionTranslationScale(&orient,&pos,&scale,&mat);
	//Matrix::CreateFromQuaternion(&orient,&mat);

	//pos.y = GAME->GetTerrain()->ComputeHeight(pos.x, pos.z);
	//mat.Translation() = pos;
}

void Building::Render(void)
{
	model->Draw(GAME->GameRenderer,&mat);
}

void Building::RenderBoundingBox(void)
{
	model->DrawBoundingBox(GAME->GameRenderer,&mat);
}
