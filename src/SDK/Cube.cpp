
#include "Cube.h"

Cube::Cube(void)
{
	VertexData = new VertexPosColor[8];
	IndexData = new unsigned short[36];

	VertexData[0].pos.Set(0.0,0.0, 0.0);
	VertexData[1].pos.Set(1.0,0.0, 0.0);
	VertexData[2].pos.Set(0.0,1.0, 0.0);
	VertexData[3].pos.Set(1.0,1.0, 0.0);
	VertexData[4].pos.Set(0.0,0.0, 1.0);
	VertexData[5].pos.Set(1.0,0.0, 1.0);
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


	IndexData[0] = 0;
	IndexData[1] = 1;
	IndexData[2] = 2;

	IndexData[3] = 1;
	IndexData[4] = 3;
	IndexData[5] = 2;

	IndexData[6] = 1;
	IndexData[7] = 5;
	IndexData[8] = 3;

	IndexData[9] = 5;
	IndexData[10] = 7;
	IndexData[11] = 3;

	IndexData[12] = 5;
	IndexData[13] = 4;
	IndexData[14] = 7;

	IndexData[15] = 4;
	IndexData[16] = 6;
	IndexData[17] = 7;

	IndexData[18] = 4;
	IndexData[19] = 0;
	IndexData[20] = 6;

	IndexData[21] = 0;
	IndexData[22] = 2;
	IndexData[23] = 6;

	IndexData[24] = 2;
	IndexData[25] = 3;
	IndexData[26] = 6;

	IndexData[27] = 3;
	IndexData[28] = 7;
	IndexData[29] = 6;

	IndexData[30] = 4;
	IndexData[31] = 5;
	IndexData[32] = 0;

	IndexData[33] = 5;
	IndexData[34] = 1;
	IndexData[35] = 0;
}

void Cube::Update(void)
{
	pos.Set(0.f, 0.f, -6.f);
	orient = orient.RotateY(&orient,GameOptions::GetInstance()->DeltaFrameTime);
	CubePos = Matrix::Identity;
	CubePos.Translate(pos);
	CubePos.RotateY(GameOptions::GetInstance()->DeltaFrameTime);
	//CubePos = Matrix::Identity;
	//CubePos.CreateFromQuaternion(&orient,&CubePos);

	VertexData[0].pos.Set(0.0,0.0, 1.0);
	VertexData[1].pos.Set(1.0,0.0, 1.0);
	VertexData[2].pos.Set(0.0,1.0, 1.0);

	VertexData[0].color = 
	VertexData[1].color =
	VertexData[2].color = Color::Green;

	VertexData[5].pos.Set(0.0,0.0, 15.0);
	VertexData[4].pos.Set(1.0,0.0, 15.0);
	VertexData[7].pos.Set(0.0,1.0, 15.0);


}

void Cube::Render(void)
{
	GAME->GameRenderer->SetModel(&CubePos);
	GAME->GameRenderer->DrawBuffer(GL_TRIANGLES,VertexData,IndexData,3);
	CubePos.RotateY(Math::ToRadians(10.f));
	GAME->GameRenderer->DrawBuffer(GL_TRIANGLES,VertexData,IndexData+12,3);
}
