
#include "TankIncludes.h"

CubeModel::~CubeModel(void)
{

}

void WriteCubeIndices(unsigned short IndexData[36])
{
	IndexData[0] = 6;
	IndexData[1] = 4;
	IndexData[2] = 5;

	IndexData[3] = 6;
	IndexData[4] = 5;
	IndexData[5] = 7;

	IndexData[6] = 7;
	IndexData[7] = 5;
	IndexData[8] = 1;

	IndexData[9] = 7;
	IndexData[10] = 1;
	IndexData[11] = 3;

	IndexData[12] = 3;
	IndexData[13] = 1;
	IndexData[14] = 0;

	IndexData[15] = 3;
	IndexData[16] = 0;
	IndexData[17] = 2;

	IndexData[18] = 2;
	IndexData[19] = 0;
	IndexData[20] = 4;

	IndexData[21] = 2;
	IndexData[22] = 4;
	IndexData[23] = 6;

	IndexData[24] = 2;
	IndexData[25] = 6;
	IndexData[26] = 7;

	IndexData[27] = 2;
	IndexData[28] = 7;
	IndexData[29] = 3;

	IndexData[30] = 4;
	IndexData[31] = 0;
	IndexData[32] = 5;

	IndexData[33] = 5;
	IndexData[34] = 0;
	IndexData[35] = 1;
}

void CubeModel::initCube(void)
{
	Name = strdup("Basic Cube");
	open = 1;
	MeshNumber = 1;

	Mesh *modelmesh = new Mesh();
	modelmesh->DrawMode = GL_TRIANGLES;
	modelmesh->TextureName = NULL;
	modelmesh->Texture = NULL;
	modelmesh->MeshName = strdup("Cube mesh");
	modelmesh->Parent = this;
	modelmesh->VertexType = vbtPosColor;

	Meshes = modelmesh;
	modelmesh->Transform = Matrix::Identity;

	modelmesh->VertexNumber = 8;
	modelmesh->IndexNumber = 36;

	modelmesh->VertexBuffer = new VertexPosColor[modelmesh->VertexNumber];
	modelmesh->IndexBuffer = new unsigned short[modelmesh->IndexNumber];

	Parent->Models.Push(this);

	VertexPosColor *VertexData = (VertexPosColor *)(modelmesh->VertexBuffer);

	VertexData[0].pos.Set(0.0,0.0,0.0);
	VertexData[1].pos.Set(1.0,0.0,0.0);
	VertexData[2].pos.Set(0.0,1.0,0.0);
	VertexData[3].pos.Set(1.0,1.0,0.0);
	VertexData[4].pos.Set(0.0,0.0,1.0);
	VertexData[5].pos.Set(1.0,0.0,1.0);
	VertexData[6].pos.Set(0.0,1.0,1.0);
	VertexData[7].pos.Set(1.0,1.0,1.0);

	VertexData[0].color.Set(0,0,0,255);
	VertexData[1].color.Set(255,0,0,255);
	VertexData[2].color.Set(0,255,0,255);
	VertexData[3].color.Set(255,255,0,255);
	VertexData[4].color.Set(0,0,255,255);
	VertexData[5].color.Set(255,0,255,255);
	VertexData[6].color.Set(0,255,255,255);
	VertexData[7].color.Set(255,255,255,255);

	WriteCubeIndices(modelmesh->IndexBuffer);

	BoundBox.center.Set(0.5,0.5,0.5);
	BoundBox.offset.Set(1.0,1.0,1.0);

	BoundSphere.center.Set(0.5,0.5,0.5);
	BoundSphere.radius = 0.5 * Math::Sqrt2;
}
