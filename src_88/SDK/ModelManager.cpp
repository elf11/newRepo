
#include "TankIncludes.h"

Mesh::Mesh(void)
{
}

Mesh::~Mesh(void)
{
	if (MeshName != NULL)
	{
		free(MeshName);
	}
	if (TextureName != NULL)
	{
		free(TextureName);
	}
	if (VertexBuffer != NULL)
	{
		free(VertexBuffer);
	}
	if (IndexBuffer != NULL)
	{
		free(IndexBuffer);
	}
}

void Mesh::DrawBoundingBox(Renderer *R,const Matrix * const World)
{
	Matrix mat;
	Matrix::Multiply(World,&Transform,&mat);
	R->SetModel(&mat);

	R->SetTexture1(NULL);

	VertexPosColor BBVertexBuffer[8];
	unsigned short BBIndexBuffer[24] = {0,1,2,3,4,5,6,7,0,4,1,5,2,6,3,7,0,2,1,3,4,6,5,7};

	float CX,CY,CZ,OX,OY,OZ;
	CX = BoundBox.center.x;
	CY = BoundBox.center.y;
	CZ = BoundBox.center.z;
	OX = BoundBox.offset.x;
	OY = BoundBox.offset.y;
	OZ = BoundBox.offset.z;

	BBVertexBuffer[0].pos.Set(CX - OX,CY - OY,CZ - OZ);
	BBVertexBuffer[1].pos.Set(CX + OX,CY - OY,CZ - OZ);
	BBVertexBuffer[2].pos.Set(CX - OX,CY + OY,CZ - OZ);
	BBVertexBuffer[3].pos.Set(CX + OX,CY + OY,CZ - OZ);
	BBVertexBuffer[4].pos.Set(CX - OX,CY - OY,CZ + OZ);
	BBVertexBuffer[5].pos.Set(CX + OX,CY - OY,CZ + OZ);
	BBVertexBuffer[6].pos.Set(CX - OX,CY + OY,CZ + OZ);
	BBVertexBuffer[7].pos.Set(CX + OX,CY + OY,CZ + OZ);

	BBVertexBuffer[0].color.Set(0,0,0,255);
	BBVertexBuffer[1].color.Set(255,0,0,255);
	BBVertexBuffer[2].color.Set(0,255,0,255);
	BBVertexBuffer[3].color.Set(255,255,0,255);
	BBVertexBuffer[4].color.Set(0,0,255,255);
	BBVertexBuffer[5].color.Set(255,0,255,255);
	BBVertexBuffer[6].color.Set(0,255,255,255);
	BBVertexBuffer[7].color.Set(255,255,255,255);

	R->DrawBuffer(GL_LINES,vbtPosColor,BBVertexBuffer,BBIndexBuffer,24);
}

void Mesh::Draw(Renderer *R,const Matrix * const World)
{
	Matrix mat;

	Matrix::Multiply(World,&Transform,&mat);

	R->SetModel(&mat);

	R->SetTexture1(Texture);

	R->DrawBuffer(DrawMode,VertexType,VertexBuffer,IndexBuffer,IndexNumber);
}

Model::Model(ModelManager *Manager)
{
	Parent = Manager;
	open = 0;
}

Model::~Model(void)
{
	if (Name != NULL)
	{
		free(Name);
	}
	delete[] Meshes;
}

Mesh * Model::GetMesh(char *Name)
{
	if (open == 0)
	{
		return NULL;
	}

	for (int i = 0;i < MeshNumber;i += 1)
	{
		if (strcmp(Name,Meshes[i].MeshName) == 0)
		{
			return &Meshes[i];
		}
	}
	return NULL;
}

class Edge
{
public:
	unsigned short index[2];
	unsigned short triangle[2];

	Edge()
	{
		index[0] = 0xFFFF;
		index[1] = 0xFFFF;
		triangle[0] = 0xFFFF;
		triangle[1] = 0xFFFF;
	}
};

int Model::LoadFromFile(char *FileName,TextureManager *TexMan)
{
	int LoadedSize;
	unsigned char *LoadedData = LoadFileBuffer(FileName,LoadedSize);
	Assert(LoadedData != NULL,"Unable to load file.");

	unsigned char *ptr = LoadedData;

#define ALIGN_4BYTES	{int tmp = (ptr - LoadedData) % 4; if(tmp > 0) { ptr += (4 - tmp); }}

	Assert((*((unsigned int *)(ptr))) == ((2 << 24) + ('m' << 16) + ('l' << 8) + ('g' << 0)),"Invalid mesh file.");

	Name = strdup(FileName);

	ptr += sizeof(unsigned int);

	memmove(&MeshNumber,ptr,sizeof(unsigned int));
	ptr += sizeof(unsigned int);
	Meshes = new Mesh[MeshNumber];

	memcpy(&BoundBox,ptr,sizeof(BoundingBox));
	ptr += sizeof(BoundingBox);
	memcpy(&BoundSphere,ptr,sizeof(BoundingSphere));
	ptr += sizeof(BoundingSphere);


	for (int i = 0;i < MeshNumber;i += 1)
	{
		Meshes[i].TextureName = strdup((const char *)(ptr));
		ptr += strlen(Meshes[i].TextureName) + 1;
	}

	ALIGN_4BYTES;

	for (int i = 0;i < MeshNumber;i += 1)
	{
/*
char				*	name;
unsigned int			searchCtrl;

Matrix					transform;
BoundingBox				boundsBox;
BoundingSphere			boundsSphere;

unsigned short			drawMode;
unsigned char			iBufferType;
unsigned char			vBufferType;
unsigned short			numIndices;
unsigned short			numVertices;

void				*	iBuffer;
void				*	vBuffer;
Texture2D			*	texture;
*/
		ptr += sizeof(char *);
		ptr += sizeof(unsigned int);

		memmove(&Meshes[i].Transform,ptr,sizeof(Matrix));
		ptr += sizeof(Matrix);

		memmove(&Meshes[i].BoundBox,ptr,sizeof(BoundingBox));
		ptr += sizeof(BoundingBox);

		memmove(&Meshes[i].BoundSphere,ptr,sizeof(BoundingSphere));
		ptr += sizeof(BoundingSphere);

		memmove(&Meshes[i].DrawMode,ptr,sizeof(unsigned short));
		ptr += sizeof(unsigned short);

		Meshes[i].IndexType = (int)(*((unsigned char *)(ptr)));
		ptr += sizeof(unsigned char);

		Meshes[i].VertexType = (int)(*((unsigned char *)(ptr)));
		ptr += sizeof(unsigned char);

		Meshes[i].IndexNumber = (int)(*((unsigned short *)(ptr)));
		ptr += sizeof(unsigned short);

		Meshes[i].VertexNumber = (int)(*((unsigned short *)(ptr)));
		ptr += sizeof(unsigned short);

		ptr += sizeof(void *);
		ptr += sizeof(void *);
		ptr += sizeof(void *);
	}

	for (int i = 0;i < MeshNumber;i += 1)
	{
		ALIGN_4BYTES;

		int VertexDataSize;
		switch (Meshes[i].VertexType)
		{
			case vbtPos :
				VertexDataSize = sizeof(VertexPos); break;
			case vbtPosColor :
				VertexDataSize = sizeof(VertexPosColor); break;
			case vbtPosTex :
				VertexDataSize = sizeof(VertexPosTex); break;
			case vbtPosNormalTex :
				VertexDataSize = sizeof(VertexPosNormalTex); break;
			case vbtPosColorTex :
				VertexDataSize = sizeof(VertexPosColorTex); break;
			case vbtPosNormalColorTex :
				VertexDataSize = sizeof(VertexPosNormalColorTex); break;
			case vbtPosNormalColorDualTex :
				VertexDataSize = sizeof(VertexPosNormalColorDualTex); break;
			case vbtPosDualTex :
				VertexDataSize = sizeof(VertexPosDualTex); break;
			case vbtPos2D :
				VertexDataSize = sizeof(VertexPos2D); break;
			case vbtPos2DColor :
				VertexDataSize = sizeof(VertexPos2DColor); break;
			case vbtPos2DTex :
				VertexDataSize = sizeof(VertexPos2DTex); break;
			case vbtPos2DColorTex :
				VertexDataSize = sizeof(VertexPos2DColorTex); break;
			case vbtPos4D :
				VertexDataSize = sizeof(VertexPos4D); break;
		};
		VertexDataSize *= Meshes[i].VertexNumber;

		Meshes[i].VertexBuffer = (void *)(new unsigned char[VertexDataSize]);
		memmove(Meshes[i].VertexBuffer,ptr,VertexDataSize);
		ptr += VertexDataSize;

		Meshes[i].IndexBuffer = new unsigned short[Meshes[i].IndexNumber];
		switch (Meshes[i].IndexType)
		{
			case 0 :
				{
					for (int z = 0;z < Meshes[i].IndexNumber;z += 1)
					{
						Meshes[i].IndexBuffer[z] = (unsigned short)(*((unsigned char *)(ptr)));
						ptr += sizeof(unsigned char);
					}
				}
			case 1 :
				{
					memmove(Meshes[i].IndexBuffer,ptr,Meshes[i].IndexNumber * sizeof(unsigned short));
					ptr += Meshes[i].IndexNumber * sizeof(unsigned short);
				}
		}

		if (Meshes[i].VertexType == vbtPos4D)
		{
			if (Meshes[i].IndexNumber & 1)
			{
				ptr += sizeof(unsigned short);

				ptr += (Meshes[i].IndexNumber / 3) * sizeof(Vector3);

				unsigned int *numEdges = (unsigned int *)(ptr);
				ptr += sizeof(unsigned int) + ((*numEdges) * sizeof(Edge));
			}
		}
		Meshes[i].MeshName = strdup((const char *)(ptr));
		ptr += strlen(Meshes[i].MeshName) + 1;
	}

	delete[] LoadedData;

	for (int i = 0;i < MeshNumber;i += 1)
	{
		Meshes[i].Texture = TexMan->GetTexture(Meshes[i].TextureName);
		Meshes[i].Parent = this;
	}

#undef ALIGN_4BYTES

	open = 1;
	return 1;
}

void Model::DrawBoundingBox(Renderer *R,const Matrix * const World)
{
	Matrix mat = *World;
	R->SetModel(&mat);

	R->SetTexture1(NULL);

	VertexPosColor BBVertexBuffer[8];
	unsigned short BBIndexBuffer[24] = {0,1,2,3,4,5,6,7,0,4,1,5,2,6,3,7,0,2,1,3,4,6,5,7};

	float CX,CY,CZ,OX,OY,OZ;
	CX = BoundBox.center.x;
	CY = BoundBox.center.y;
	CZ = BoundBox.center.z;
	OX = BoundBox.offset.x;
	OY = BoundBox.offset.y;
	OZ = BoundBox.offset.z;


	BBVertexBuffer[0].pos.Set(CX - OX,CY - OY,CZ - OZ);
	BBVertexBuffer[1].pos.Set(CX + OX,CY - OY,CZ - OZ);
	BBVertexBuffer[2].pos.Set(CX - OX,CY + OY,CZ - OZ);
	BBVertexBuffer[3].pos.Set(CX + OX,CY + OY,CZ - OZ);
	BBVertexBuffer[4].pos.Set(CX - OX,CY - OY,CZ + OZ);
	BBVertexBuffer[5].pos.Set(CX + OX,CY - OY,CZ + OZ);
	BBVertexBuffer[6].pos.Set(CX - OX,CY + OY,CZ + OZ);
	BBVertexBuffer[7].pos.Set(CX + OX,CY + OY,CZ + OZ);

	BBVertexBuffer[0].color.Set(0,0,0,255);
	BBVertexBuffer[1].color.Set(255,0,0,255);
	BBVertexBuffer[2].color.Set(0,255,0,255);
	BBVertexBuffer[3].color.Set(255,255,0,255);
	BBVertexBuffer[4].color.Set(0,0,255,255);
	BBVertexBuffer[5].color.Set(255,0,255,255);
	BBVertexBuffer[6].color.Set(0,255,255,255);
	BBVertexBuffer[7].color.Set(255,255,255,255);

	R->DrawBuffer(GL_LINES,vbtPosColor,BBVertexBuffer,BBIndexBuffer,24);

	for (int i = 0;i < MeshNumber;i += 1)
	{
//		Meshes[i].DrawBoundingBox(R,World);
	}
}

void Model::Draw(Renderer *R,const Matrix * const World)
{
	if (open == 0)
	{
		return;
	}
	for (int i = 0;i < MeshNumber;i += 1)
	{
		Meshes[i].Draw(R,World);
	}
}

ModelManager::ModelManager(TextureManager *TM,Renderer *R)
{
	Models.SetLength(0);
	TexMan = TM;
	Ren = R;
}

ModelManager::~ModelManager(void)
{
	for (int i = 0;i < Models.Length();i += 1)
	{
		delete Models[i];
	}
}

Model * ModelManager::GetModel(char *FileName)
{
	for (int i = 0;i < Models.Length();i += 1)
	{
		if (strcmp(FileName,Models[i]->Name) == 0)
		{
			return Models[i];
		}
	}
	Model *newModel = new Model(this);
	if (newModel->LoadFromFile(FileName,TexMan) != 0)
	{
		Models.Push(newModel);
		return newModel;
	}
	else
	{
		delete newModel;
		return NULL;
	}
}
