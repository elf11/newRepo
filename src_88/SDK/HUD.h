
#ifndef HUD__H
#define HUD__H

#include "TankIncludes.h"

struct CharSize
{
	float U1,U2;
	int pixels;
};


class HUDRenderer
{
private :
	static const int BufferLen = 8192;
	VertexPos2DTex Buffer[BufferLen * 4];

	static int IndexInit;
	static unsigned short IndexData[BufferLen * 6];
public :
	int loaded;
	Texture2D *FontImage;

	CharSize chars[256];

	HUDRenderer(void);
	~HUDRenderer(void);

	void LoadTextData(char *FontImageFileName,char *FontDataFileName);

	int TextPixelHeight(void);
	int TextPixelLength(char *Text,int len);
	void DrawText(int x,int y,char *Text,int len);

	void DrawImage(int x,int y,int w,int h,float u1,float v1,float u2,float v2);
};

#endif