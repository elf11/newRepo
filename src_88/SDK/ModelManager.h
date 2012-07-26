
#ifndef MODELMANAGER__H
#define MODELMANAGER__H

#include "utils/RArray.h";
#include "TankIncludes.h"

class Texture2D;
class TextureManager;
class Model;
class ModelManager;
class Renderer;

class Mesh
{
public :
	Model *Parent;

	int open;

	char *MeshName;
	char *TextureName;

	Matrix Transform;
	BoundingBox BoundBox;
	BoundingSphere BoundSphere;

	unsigned short DrawMode;
	int VertexType;
	int IndexType;

	int VertexNumber;
	int IndexNumber;

	void *VertexBuffer;
	unsigned short *IndexBuffer;

	Texture2D *Texture;

	friend class Model;

	Mesh(void);
	~Mesh(void);

	void Draw(Renderer *R,const Matrix * const World);
	void DrawBoundingBox(Renderer *R,const Matrix * const World);
};


class Model
{
public :
	char *Name;
	ModelManager *Parent;

	int open;

	int MeshNumber;
	Mesh *Meshes;

	BoundingBox BoundBox;
	BoundingSphere BoundSphere;

	friend class ModelManager;


	Model(ModelManager *Manager);
	~Model(void);

	Mesh *GetMesh(char *Name);

	int LoadFromFile(char *FileName,TextureManager *TexMan);

	void Draw(Renderer *R,const Matrix * const World);
	void DrawBoundingBox(Renderer *R,const Matrix * const World);
};

class ModelManager
{
public :

	TextureManager *TexMan;
	Renderer *Ren;
	Array<Model *> Models;

	ModelManager(TextureManager *TM,Renderer *R);
	~ModelManager();

	Model *GetModel(char *FileName);
};

#endif
