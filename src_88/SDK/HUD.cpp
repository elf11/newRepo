
#include "TankIncludes.h"

int HUDRenderer::IndexInit = 0;
unsigned short HUDRenderer::IndexData[HUDRenderer::BufferLen * 6];

HUDRenderer::HUDRenderer(void)
{
	loaded = 0;
	if (IndexInit == 0)
	{
		for (int i = 0;i < BufferLen;i += 1)
		{
			IndexData[i * 6 + 0] = i * 4 + 0;
			IndexData[i * 6 + 1] = i * 4 + 1;
			IndexData[i * 6 + 2] = i * 4 + 2;
			IndexData[i * 6 + 3] = i * 4 + 2;
			IndexData[i * 6 + 4] = i * 4 + 1;
			IndexData[i * 6 + 5] = i * 4 + 3;
		}
		IndexInit = 1;
	}
}

HUDRenderer::~HUDRenderer(void)
{

}

char *SkipNonSpace(char *s)
{
	while ((s[0] != ' ') && (s[0] != '\n') && (s[0] != '\r') && (s[0] != '\t'))
	{
		s += 1;
	}
	while (((s[0] == ' ') || (s[0] == '\n') || (s[0] == '\r') || (s[0] == '\t')) && (s[0] != 0))
	{
		s += 1;
	}
	return s;
}

void HUDRenderer::LoadTextData(char *FontImageFileName,char *FontDataFileName)
{
	FontImage = GAME->TexMan->GetTexture(FontImageFileName);
	int size;
	unsigned char * data = LoadFileBuffer(FontDataFileName,size);
	char * ptr = (char*)(data);
	for (int i = 32;i < 127;i += 1)
	{
		sscanf(ptr,"%d %f %f %d",&i,&chars[i].U1,&chars[i].U2,&chars[i].pixels);
		ptr = SkipNonSpace(ptr);
		ptr = SkipNonSpace(ptr);
		ptr = SkipNonSpace(ptr);
		ptr = SkipNonSpace(ptr);
	}

	loaded = 1;
}

int HUDRenderer::TextPixelHeight(void)
{
	return 16;
}

int HUDRenderer::TextPixelLength(char *Text,int len)
{
	if (loaded == 0)
	{
		return 0;
	}
	int s = 0;
	for (int i = 0;i < len;i += 1)
	{
		s += chars[Text[i]].pixels + 2;
	}
	s -= 2;
	return s;
}

void HUDRenderer::DrawText(int x,int y,char *Text,int len)
{
	if (loaded == 0)
	{
		return;
	}
	Matrix mat = Matrix::Identity;
	GAME->GameRenderer->SetModel(&mat);
	GAME->GameRenderer->SetTexture1(FontImage);
	while (len > 0)
	{
		int templen = Math::Min(len,BufferLen);
		for (int i = 0;i < templen;i += 1)
		{
			Buffer[i * 4 + 0].pos.Set(x,y);
			Buffer[i * 4 + 1].pos.Set(x,y + FontImage->height);
			Buffer[i * 4 + 2].pos.Set(x + chars[Text[i]].pixels,y);
			Buffer[i * 4 + 3].pos.Set(x + chars[Text[i]].pixels,y + FontImage->height);
			Buffer[i * 4 + 0].tex.Set(chars[Text[i]].U1,0.0);
			Buffer[i * 4 + 1].tex.Set(chars[Text[i]].U1,1.0);
			Buffer[i * 4 + 2].tex.Set(chars[Text[i]].U2,0.0);
			Buffer[i * 4 + 3].tex.Set(chars[Text[i]].U2,1.0);
			x += chars[Text[i]].pixels + 2;
		}
		GAME->GameRenderer->DrawBuffer(GL_TRIANGLES,Buffer,IndexData,templen * 6);
		Text += templen;
		len -= templen;
	}
}

void HUDRenderer::DrawImage(int x,int y,int w,int h,float u1,float v1,float u2,float v2)
{
	if (loaded == 0)
	{
		return;
	}
	Matrix mat = Matrix::Identity;
	GAME->GameRenderer->SetModel(&mat);

	Buffer[0].pos.Set(x,y);
	Buffer[1].pos.Set(x,y + h);
	Buffer[2].pos.Set(x + w,y);
	Buffer[3].pos.Set(x + w,y + h);
	Buffer[0].tex.Set(u1,v1);
	Buffer[1].tex.Set(u1,v2);
	Buffer[2].tex.Set(u2,v1);
	Buffer[3].tex.Set(u2,v2);
	GAME->GameRenderer->DrawBuffer(GL_TRIANGLES,Buffer,IndexData,6);
}
