
#include "TerainMap.h"

unsigned char *LoadBinaryFile(char *FileName)
{
	//Deschide fisierul
	FILE *F = fopen(FileName,"rb");
	Assert(F != 0,"Unable to load binary file.");

	//Afla lungimea fisierului
	fseek(F,0,SEEK_END);
	long size = ftell(F);
	fseek(F,0,SEEK_SET);

	//Initializeaza bufferul
	unsigned char *temp = new unsigned char[size + 1];
	memset(temp,0,size + 1);

	//Citeste sursa
	fread(temp,1,size,F);

	//Inchide fisierul
	fclose(F);

	//Intoarce bufferul unde se afla sursa
	return temp;
}

void TerainMap::initializeTerainMap(float HeightMap[256][256]){

	unsigned char * buffer = LoadBinaryFile("hmap.raw");

	srand(GetTime());
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 256; j++){
				HeightMap[i][j] = ((unsigned char)(buffer[i * 256 + j]));
				HeightMap[i][j] /= 20;
		}
	}

}

TerainMap::TerainMap(void)
{
	VertexData = new VertexPosColor[65536];
	IndexData = new unsigned short[261630];

	float HeightMap[256][256];
	initializeTerainMap(HeightMap);

	for(int i = 0; i < 256; i++){	
		for(int j= 0; j < 256; j++){
			VertexData[i*256+j].pos.Set(i,HeightMap[i][j],j);
			VertexData[i*256+j].color.Set(0,150 + rand() % 70 - 35,0,255);
		}
	}

	int k = 0;
	for(int i = 0; i < 255; i++){
		for(int j = 0; j < 256; j++, k+=2){

			IndexData[k] = i*256+j;
			IndexData[k+1] = (i+1)*256 + j;
		}
		IndexData[k] = (i+1)*256+255;
		for(int j = 255; j >= 0; j--, k+=2){

			IndexData[k] = i*256+j;
			IndexData[k+1] = (i+1)*256 + j;
		}
		IndexData[k] = (i+1)*256+0;
	}


}

void TerainMap::Update(void)
{
//	orient = orient.RotateY(&orient,GAME->DeltaFrameTime);
}


void TerainMap::Render(void)
{
	TerainMapPos.CreateFromQuaternion(&orient,&TerainMapPos);
	TerainMapPos.Translate(pos);
	GAME->GameRenderer->SetModel(&TerainMapPos);
	GAME->GameRenderer->DrawBuffer(GL_TRIANGLE_STRIP,VertexData,IndexData,261630);
}