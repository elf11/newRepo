
#include "TankIncludes.h"

TerrainMapModel::~TerrainMapModel(void)
{
	delete[] HeightMap;
}

void TerrainMapModel::initializeTerainMap(char *FileName,char *TextureName)
{
	if (this->open != 0)
	{
		return;
	}

	int size;
	unsigned char * buffer = LoadFileBuffer(FileName,size);
	MapWidth = MapHeight = Math::Round(Math::Sqrt(size));

	int i,j,k;

	HeightMap = new float[MapWidth * MapHeight];

	for(i = 0,k = 0;i < MapHeight;i += 1)
	{
		for(j = 0;j < MapWidth;j += 1,k += 1)
		{
			HeightMap[k] = ((float)(buffer[k]));
		}
	}

	Name = strdup(FileName);
	open = 1;
	MeshNumber = 1;

	Mesh *modelmesh = new Mesh();
	modelmesh->DrawMode = GL_TRIANGLE_STRIP;
	modelmesh->TextureName = strdup(TextureName);
	modelmesh->Texture = Parent->TexMan->GetTexture(modelmesh->TextureName);
	modelmesh->MeshName = strdup("Terrain mesh");
	modelmesh->Parent = this;
	modelmesh->VertexType = vbtPosTex;

	Meshes = modelmesh;
	modelmesh->Transform = Matrix::Identity;

	modelmesh->VertexNumber = MapWidth * MapHeight;
	modelmesh->IndexNumber = (4 * MapWidth * (MapHeight - 1)) + (MapHeight - 2) * 2;

	modelmesh->VertexBuffer = new VertexPosTex[MapWidth * MapHeight];
	modelmesh->IndexBuffer = new unsigned short[modelmesh->IndexNumber];

	Parent->Models.Push(this);

	VertexPosTex *VertexData = (VertexPosTex *)(modelmesh->VertexBuffer);

	for(i = 0,k = 0;i < MapHeight;i += 1)
	{
		for(j = 0;j < MapWidth;j += 1,k += 1)
		{
			VertexData[k].pos.Set(j,HeightMap[k],i);
			VertexData[k].tex.Set(((float)(j)) / (MapWidth - 1),((float)(i)) / (MapHeight - 1));
		}
	}

	k = 0;
	for(i = 0;i < MapHeight - 1;)
	{
		for(j = 0;j < MapWidth;j += 1,k += 2)
		{
			modelmesh->IndexBuffer[k] = (i * MapWidth) + j;
			modelmesh->IndexBuffer[k+1] = ((i + 1) * MapWidth) + j;
		}
		i += 1;
		if (i == MapHeight - 1)
		{
			break;
		}

		modelmesh->IndexBuffer[k] = (i + 1) * MapWidth + MapWidth - 1;
		k += 1;
		modelmesh->IndexBuffer[k] = (i + 1) * MapWidth + MapWidth - 1;
		k += 1;

		for(j = MapWidth - 1;j >= 0;j -= 1,k += 2)
		{
			modelmesh->IndexBuffer[k] = ((i + 1) * MapWidth) + j;
			modelmesh->IndexBuffer[k+1] = (i * MapWidth) + j;
		}
		i += 1;

		modelmesh->IndexBuffer[k] = (i + 1) * MapWidth;
		k += 1;
		modelmesh->IndexBuffer[k] = (i + 1) * MapWidth;
		k += 1;
	}

}

TerrainMap::TerrainMap(TerrainMapModel *data) : BaseObject()
{
	model = data;

	WidthRatio = 1.0;
	HeightRatio = 1.0;
	VerticalRatio = 1.0 / 2;

	type = otTerrain;
}

TerrainMap::~TerrainMap(void)
{

}

float TerrainMap::MaxXPos(void)
{
	return (GetTerrainModel()->MapWidth - 1) * WidthRatio;
}

float TerrainMap::MaxZPos(void)
{
	return (GetTerrainModel()->MapHeight - 1) * HeightRatio;
}

void TerrainMap::Update(void)
{

}

void TerrainMap::Render(void)
{
	Matrix MatScale = Matrix::Identity;
	MatScale.Scale(WidthRatio,VerticalRatio,HeightRatio);

	Matrix TerrainPos;

	TerrainPos.CreateFromQuaternion(&orient,&TerrainPos);
	TerrainPos.Translate(pos);

	TerrainPos = TerrainPos * MatScale;

	model->Draw(GAME->GameRenderer,&TerrainPos);
}



float TerrainMap::ComputeHeight(float x,float z)
{
	x -= pos.x;
	z -= pos.z;
	if ((x < 0) || (z < 0) || (x >= ((GetTerrainModel()->MapWidth - 1) * WidthRatio)) || (z >= ((GetTerrainModel()->MapHeight - 1) * HeightRatio)))
	{
		return 0;
	}
	int px = Math::Floor(x / WidthRatio);
	int pz = Math::Floor(z / HeightRatio);
	x = Math::Fmod(x / WidthRatio,1.0);
	z = Math::Fmod(z / HeightRatio,1.0);

	float a,b,c,d;
	if (z <= 1.0 - x)
	{	
		//Triunghiul de sus
		a = GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px];
		b = GetTerrainModel()->HeightMap[(pz + 1) * GetTerrainModel()->MapWidth + px];
		c = GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px + 1];
		d = b + c - a;
	}
	else
	{
		//cel de jos
		b = GetTerrainModel()->HeightMap[(pz + 1) * GetTerrainModel()->MapWidth + px];
		c = GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px + 1];
		d = GetTerrainModel()->HeightMap[(pz + 1) * GetTerrainModel()->MapWidth + px + 1];
		a = b + c - d;
	}
	float z1,z2;
	z1 = a * (1 - z) + b * z;
	z2 = c * (1 - z) + d * z;
	return (z1 * (1 - x) + z2 * x) * VerticalRatio;
}

void TerrainMap::ComputeNormal(float x,float z,Vector3 &v)
{
	x -= pos.x;
	z -= pos.z;
	if ((x < 0) || (z < 0) || (x >= ((GetTerrainModel()->MapWidth - 1) * WidthRatio)) || (z >= ((GetTerrainModel()->MapHeight - 1) * HeightRatio)))
	{
		v.Set(0.0,1.0,0.0);
		return;
	}

	Vector3 heightv;
	Vector3 widthv;

	int px = Math::Floor(x / WidthRatio);
	int pz = Math::Floor(z / HeightRatio);

	heightv.x = 0;
	heightv.y = GetTerrainModel()->HeightMap[(pz + 1) * GetTerrainModel()->MapWidth + px] - GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px];
	heightv.z = 1;

	widthv.x = 1;
	widthv.y = GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px] - GetTerrainModel()->HeightMap[pz * GetTerrainModel()->MapWidth + px + 1];
	widthv.z = 0;

	Vector3::Cross(&heightv,&widthv,&v);
	v.Normalize();
}

//TODO
void ComputeDesired(Vector3 &pivot,Vector3 &desired,float angle)
{
	Vector3 temp = pivot - desired;
	float phi = atan2(temp.z,temp.x);

	Matrix Rot1,Rot2;
	Matrix::CreateFromYawPitchRoll(phi,0,0,&Rot1);
	Matrix::CreateFromYawPitchRoll(0,angle,0,&Rot2);

	Rot1.Transpose();
	temp = Rot1 * temp;
	temp = Rot2 * temp;
	Rot1.Transpose();
	temp = Rot1 * temp;

	desired = pivot + temp;
}

void TerrainMap::ComputePointPosition(Vector3 &pivot,Vector3 &desired)
{
	desired.y = pivot.y;
	if (ComputeHeight(desired.x,desired.z) < desired.y)
	{
		float maxangle = 90;
		float minangle = 0;
	}

}
