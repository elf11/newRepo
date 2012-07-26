#pragma once

//#include "GraphicsComponents.h"
#include "ManagedArray.h"
#include "Matrix.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
//#include "BufferObject.h"

class Texture2D;

class Mesh
{
public:
	char				*	name;
	unsigned int			searchCtrl;
	
	Matrix					transform;
	BoundingBox				boundsBox;
	BoundingSphere			boundsSphere;
	
	unsigned short			drawMode;
	unsigned char			iBufferType;
	unsigned char			vBufferType;
	unsigned short			numIndices;
	unsigned short			numVertices;
	
	void				*	iBuffer;
	void				*	vBuffer;
	Texture2D			*	texture;
	
	void Draw() const;
    void DrawElements() const;


	//intersects mesh with ray defined by origin ro and direction rd
	//returns intersection point in ip (if exists)
	float IntersectsRay(const Vector3& ro, const Vector3& rd, Vector3* ip);
	static float IntersectsTri(const Vector3& ro, const Vector3& rd, const Vector3& p1, const Vector3& p2, const Vector3& p3, Vector3* ip);
};

class Model : public ManagedArray<Model, 1024>
{
public:
	class BufferObjectMeshes
	{
	public:
		Mesh		 *	meshes;
		~BufferObjectMeshes();
	};
	
	static const unsigned	Version;
	unsigned char *			data;
	
	char *					textureName;
	char *					path;
	unsigned int			searchCtrl;
	
	~Model();
	
	unsigned int			numMeshes;
	BoundingBox				boundsBox;
	BoundingSphere			boundsSphere;

	unsigned int			sizeVertices;
	unsigned int			sizeIndices;
	
	Mesh				*	meshes;
	BufferObjectMeshes	*	buffer;
	
	Mesh * FindMesh(const char *const name) const;
	Mesh * FindMeshBuffer(const char *const name) const;
	void PrintMeshes() const;

	void LoadTextures(void);	
	void Render(const Matrix *const World) const;

	static Model * Find(const char *const file);
	static Model * Load(const char *const file, const bool loadTextures = true);
    static Model * CreateEmpty();

	static Model        * Screen;
    
    static void Init();
    static void LoadAll();
    static void CreateBufferObjectAll();
};
