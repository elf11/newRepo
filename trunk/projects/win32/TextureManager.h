/*#ifndef TEXTUREMANAGER__H
#define TEXTUREMANAGER__H

#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"
#include "utils/RArray.h";

class TextureManager;

class Texture2D : public BaseObject
{
public:
	TextureManager *Manager;
public:
	char *FileName;

	void *VertexBuffer;
	GLshort *IndexBuffer;

	void LoadFromFile(char *FileName);
	void LoadBuffer(

}

class TextureManager
{
public:
	TextureManager(void);
};
#endif
*/