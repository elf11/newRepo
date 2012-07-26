#ifndef TEXTUREMANAGER__H
#define TEXTUREMANAGER__H

#include "utils/RArray.h";
#include "TankIncludes.h"

class TextureManager;
class Texture2D;

class Texture2D
{
public:
	TextureManager *Manager;
public:
	char *FileName;

	unsigned char *PixelData;
	int height, width;

	GLuint ptr;
	
	Texture2D(void);
	~Texture2D(void);

	int LoadFromFile(char *FileName);
	int LoadBuffer(unsigned char * Buffer, int length);

	GLuint getPtr(void);

};



class TextureManager
{
private :
	Array<Texture2D *> Textures;
public:
	TextureManager(void);
	~TextureManager(void);

	Texture2D * GetTexture(char * FileName);
};

#endif
