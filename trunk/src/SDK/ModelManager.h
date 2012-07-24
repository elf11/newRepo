
#ifndef MODELMANAGER__H
#define MODELMANAGER__H

#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"
#include "utils/RArray.h";

class BaseObject;
class Texture2D;

class ModelManager;
class Mesh : public BaseObject 
{
private :
	ModelManager *Parent;

	int open;

	char *MeshName;
	char *TextureName;

	GLuint DrawMode;
	int VertexType;

	int VertexNumber;
	int IndexNumber;

	void *VertexBuffer;
	GLshort *IndexBuffer;

	Texture2D *Texture;
public :
	Mesh(ModelManager *Manager);

	void LoadFromFile(char *FileName);
	void Draw(void);
};

class ModelManager
{
	Array<Mesh> Meshes;
public :
	ModelManager(void);

	Mesh *GetMesh(char *FileName);
};

#endif
