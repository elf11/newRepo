
#include "TankIncludes.h"

SkyBox::SkyBox(void)
{
	scale.Set(20000.0,20000.0,20000.0);
	pos.y = -500;
	type = otSky;
}

SkyBox::~SkyBox(void)
{
}

void SkyBox::Update(void)
{

}

void SkyBox::Render(void)
{
	glDisable(GL_CULL_FACE);
	glCullFace(GL_NONE);
	Matrix MatScale = Matrix::Identity;
	MatScale.Scale(scale);

	Matrix SkyPos;

	SkyPos.CreateFromQuaternion(&orient,&SkyPos);
	SkyPos.Translate(GAME->PlayerCamera->pos);
	SkyPos.Translate(pos);

	SkyPos = SkyPos * MatScale;

	model->Draw(GAME->GameRenderer,&SkyPos);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void SkyBox::RenderBoundingBox(void)
{
	glDisable(GL_CULL_FACE);
	glCullFace(GL_NONE);
	Matrix MatScale = Matrix::Identity;
	MatScale.Scale(scale);

	Matrix SkyPos;

	SkyPos.CreateFromQuaternion(&orient,&SkyPos);
	SkyPos.Translate(GAME->PlayerCamera->pos);
	SkyPos.Translate(pos);

	SkyPos = SkyPos * MatScale;

	model->DrawBoundingBox(GAME->GameRenderer,&SkyPos);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

/*void CubeMapModel::initializeCubeMap(char *TextureNamePosX,char *TextureNameNegX,char *TextureNamePosY,char *TextureNameNegY,
									 char *TextureNamePosZ,char *TextureNameNegZ)
{
	Name = strdup("Cube map");
	open = 1;
	MeshNumber = 6;


	Meshes = new Mesh[6];

	Meshes[0].TextureName = strdup(TextureNamePosX);
	Meshes[0].MeshName = strdup("Cube map pos x");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapPosX);

	Meshes[1].TextureName = strdup(TextureNameNegX);
	Meshes[1].MeshName = strdup("Cube map neg x");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapNegX);

	Meshes[2].TextureName = strdup(TextureNamePosY);
	Meshes[2].MeshName = strdup("Cube map pos y");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapPosY);

	Meshes[3].TextureName = strdup(TextureNameNegY);
	Meshes[3].MeshName = strdup("Cube map neg y");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapNegY);

	Meshes[4].TextureName = strdup(TextureNamePosZ);
	Meshes[4].MeshName = strdup("Cube map pos z");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapPosZ);

	Meshes[5].TextureName = strdup(TextureNameNegZ);
	Meshes[5].MeshName = strdup("Cube map neg z");
	Meshes[0].Texture = Parent->TexMan->GetTexture(Meshes[0].TextureName,ttCubeMapNegZ);

	for (int i = 0;i < 6;i += 1)
	{
		Meshes[i].DrawMode = GL_TRIANGLE_STRIP;
		Meshes[i].Parent = this;
		Meshes[i].VertexType = vbtPosTex;

		Meshes[i].Transform = Matrix::Identity;

		Meshes[i].VertexNumber = 4;
		Meshes[i].IndexNumber = 4;

		Meshes[i].VertexBuffer = new VertexPosTex[4];
		Meshes[i].IndexBuffer = new unsigned short[4];
		for (int j = 0;j < 4;j += 1)
		{
			Meshes[i].IndexBuffer[j] = j;
		}

	}

	Parent->Models.Push(this);

	VertexPosTex *Data;
	Data = (VertexPosTex *)(Meshes[0].VertexBuffer);
	Data[0].pos.Set(1.0,1.0,-1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(1.0,-1.0,-1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(1.0,1.0,1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(1.0,-1.0,1.0);
	Data[3].tex.Set(1.0,1.0);

	Data = (VertexPosTex *)(Meshes[1].VertexBuffer);
	Data[0].pos.Set(-1.0,1.0,1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(-1.0,-1.0,1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(-1.0,1.0,-1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(-1.0,-1.0,-1.0);
	Data[3].tex.Set(1.0,1.0);

	Data = (VertexPosTex *)(Meshes[2].VertexBuffer);
	Data[0].pos.Set(-1.0,1.0,1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(-1.0,1.0,-1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(1.0,1.0,1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(1.0,1.0,-1.0);
	Data[3].tex.Set(1.0,1.0);

	Data = (VertexPosTex *)(Meshes[3].VertexBuffer);
	Data[0].pos.Set(-1.0,-1.0,-1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(-1.0,-1.0,1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(1.0,-1.0,-1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(1.0,-1.0,1.0);
	Data[3].tex.Set(1.0,1.0);

	Data = (VertexPosTex *)(Meshes[4].VertexBuffer);
	Data[0].pos.Set(1.0,1.0,1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(1.0,-1.0,1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(-1.0,1.0,1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(-1.0,-1.0,1.0);
	Data[3].tex.Set(1.0,1.0);

	Data = (VertexPosTex *)(Meshes[5].VertexBuffer);
	Data[0].pos.Set(-1.0,1.0,-1.0);
	Data[0].tex.Set(0.0,0.0);
	Data[1].pos.Set(-1.0,-1.0,-1.0);
	Data[1].tex.Set(0.0,1.0);
	Data[2].pos.Set(1.0,1.0,-1.0);
	Data[2].tex.Set(1.0,0.0);
	Data[3].pos.Set(1.0,-1.0,-1.0);
	Data[3].tex.Set(1.0,1.0);

}

CubeMap::CubeMap(void)
{
	pos.Set(0.0,0.0,0.0);
	Scale = 1.0;
}

void CubeMap::Update(void)
{
//	orient = orient.RotateY(&orient,GAME->DeltaFrameTime);
}

void CubeMap::Render(void)
{
	Matrix CubeMapPos;
	CubeMapPos.CreateFromQuaternion(&orient,&CubeMapPos);
	CubeMapPos.Scale(Scale);
	this->model->Draw(GAME->GameRenderer,&CubeMapPos);
}
*/