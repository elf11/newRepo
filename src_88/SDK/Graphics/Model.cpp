
#include "Renderer.h"
#include "..\..\..\platforms\win32\include\fs\FileDisk.h"
#include "Model.h"
#include <string.h>

#define DEBUG_OUT(x)

Model        * Model::Screen        = NULL;

const unsigned Model::Version =	('g' << 0) |
								('l' << 8) |
								('m' << 16) |
								(2 << 24);

void Model::Init()
{
}

void Mesh::Draw() const
{
/*#ifndef _DEDICATED_SERVER
	switch (vBufferType)
	{
		case VertexBufferType::Pos:
			if(iBufferType == IndexBufferType::UnsignedByte)
				Graphics::Instance->DrawElements(drawMode, (VertexPos *) vBuffer, (unsigned char *) iBuffer, numIndices);
			else
				Graphics::Instance->DrawElements(drawMode, (VertexPos *) vBuffer, (unsigned short *) iBuffer, numIndices);
			break;
			//case VertexBufferType::PosColor:			
		case VertexBufferType::PosTex:
			if(iBufferType == IndexBufferType::UnsignedByte)
				Graphics::Instance->DrawElements(drawMode, (VertexPosTex *) vBuffer, (unsigned char *) iBuffer, numIndices);
			else
				Graphics::Instance->DrawElements(drawMode, (VertexPosTex *) vBuffer, (unsigned short *) iBuffer, numIndices);
			break;
		case VertexBufferType::PosNormalTex:
			if(iBufferType == IndexBufferType::UnsignedByte)
				Graphics::Instance->DrawElements(drawMode, (VertexPosNormalTex *) vBuffer, (unsigned char *) iBuffer, numIndices);
			else
				Graphics::Instance->DrawElements(drawMode, (VertexPosNormalTex *) vBuffer, (unsigned short *) iBuffer, numIndices);
			break;
			//case VertexBufferType::PosColorTex:
			//case VertexBufferType::PosNormalColorTex:
			//case VertexBufferType::PosNormalColorDualTex:
			//case VertexBufferType::PosDualTex:
			//case VertexBufferType::Pos2D:
			//case VertexBufferType::Pos2DColor:
			//case VertexBufferType::Pos2DTex:
			//case VertexBufferType::Pos2DColorTex:	
			//case VertexBufferType::Pos4D:	
	}
#endif*/
}

unsigned int GenerateSearchCtrl(const char *s)
{
	unsigned int searchCtrl = 0;
	if(s != NULL)
		while (*s != '\0') searchCtrl += *(s++);
	return searchCtrl;
}

Model::BufferObjectMeshes::~BufferObjectMeshes()
{
	delete [] meshes;
}

Model::~Model()
{
	Texture2D *tex = NULL;
	
	for (Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		tex = m->texture;
		if(tex)
		{
			delete tex;
			for (Mesh *n = m + 1; n < end; ++n)
				if (n->texture == tex)
					n->texture = NULL;
			m->texture = NULL;
		}
	}
	
	delete [] path;
	delete [] data;
	if(buffer)
		delete buffer;
}

Model * Model::Find(const char *const file)
{
	unsigned int searchCtrl = GenerateSearchCtrl(file);
	
	for(Model *const* m = array, *const*const end = array + numElements; m < end; ++m)
		if((*m)->searchCtrl == searchCtrl && strcmp((*m)->path, file) == 0)
			return (*m);
	
	return NULL;
}

Mesh * Model::FindMesh(const char *const name) const
{
	unsigned int searchCtrl = GenerateSearchCtrl(name);
	
	for (Mesh *mesh = meshes, *const end = mesh + numMeshes; mesh < end; ++mesh)
		if(mesh->searchCtrl == searchCtrl && strcmp(mesh->name, name) == 0)
			return mesh;

	return NULL;
}

Mesh * Model::FindMeshBuffer(const char *const name) const
{
	if(buffer)
	{
		unsigned int searchCtrl = GenerateSearchCtrl(name);		
		for (Mesh *mesh = buffer->meshes, *const end = mesh + numMeshes; mesh < end; ++mesh)
			if(mesh->searchCtrl == searchCtrl && strcmp(mesh->name, name) == 0)
				return mesh;
	}
	return NULL;
}

void Model::PrintMeshes() const
{
	int i = 0;
	DEBUG_OUT("meshes for model %s",path);
	for (Mesh *mesh = buffer->meshes, *const end = mesh + numMeshes; mesh < end; ++mesh)
	{
		DEBUG_OUT("[%d] %s",i++,mesh->name);
	}

}

Model * Model::Load(const char *const file, const bool loadTextures)
{

	if (!strcmp(file,"data/models/bf109.glm"))
		DEBUG_OUT("break");

#define ALIGN_4BYTES	{tmp = (ptr - model->data) % 4; if(tmp > 0) { ptr += (4 - tmp); }}
	Model *model = Find(file);
	if(model)		
	{
		//if (loadTextures)
		//	model->LoadTextures(filter, wrap);
		return model;
	}
	
	File *fs = FILEMGR->Open(file);
	if(fs == NULL)	return NULL;
	
	unsigned char *ptr = new unsigned char[fs->Size()];
	fs->Read(ptr, fs->Size());
	delete fs;
	unsigned int tmp = *((unsigned int *) ptr);
	
	if(tmp != Version)
	{
		delete [] ptr;
		return NULL;
	}
	
	model = new Model;
	model->data = ptr;
	model->path = new char[strlen(file) + 1];
	strcpy(model->path, file);
	model->searchCtrl = GenerateSearchCtrl(model->path);
	
	ptr += sizeof(unsigned int); // Version
	memcpy(&model->numMeshes,	ptr, sizeof(unsigned int));		ptr += sizeof(unsigned int);
	memcpy(&model->boundsBox,	ptr, sizeof(BoundingBox));		ptr += sizeof(BoundingBox);
	memcpy(&model->boundsSphere,ptr, sizeof(BoundingSphere));	ptr += sizeof(BoundingSphere);
	
	model->textureName = (char*)ptr; //save texture name, maybe we need it.

	for(unsigned i = 0; i < model->numMeshes; ++i)
	{
		
		while (*ptr != '\0') ++ptr;
		++ptr;
	}
	
	ALIGN_4BYTES
	
	model->meshes = (Mesh *) ptr;								ptr += model->numMeshes * sizeof(Mesh);
	model->buffer = NULL;
	model->sizeVertices = 0;
	model->sizeIndices  = 0;
	
	for (Mesh *m = model->meshes, *end = m + model->numMeshes; m < end; ++m)
	{
		ALIGN_4BYTES
		
		m->vBuffer = ptr;
		switch (m->vBufferType)
		{
			case VertexBufferType::Pos:
				ptr += m->numVertices * sizeof(VertexPos);
				break;
				//case VertexBufferType::PosColor:			
			case VertexBufferType::PosTex:
				ptr += m->numVertices * sizeof(VertexPosTex);
				break;
			case VertexBufferType::PosNormalTex:
				ptr += m->numVertices * sizeof(VertexPosNormalTex);
				break;
				//case VertexBufferType::PosColorTex:
				//case VertexBufferType::PosNormalColorTex:
				//case VertexBufferType::PosNormalColorDualTex:
				//case VertexBufferType::PosDualTex:
				//case VertexBufferType::Pos2D:
				//case VertexBufferType::Pos2DColor:
				//case VertexBufferType::Pos2DTex:
				//case VertexBufferType::Pos2DColorTex:
			case VertexBufferType::Pos4D:
				ptr += m->numVertices * sizeof(VertexPos4D);
				break;
		}
		model->sizeVertices += ptr - ((unsigned char *)m->vBuffer);
		
		m->iBuffer = ptr;
		if(m->iBufferType == IndexBufferType::UnsignedByte)
			ptr += m->numIndices * sizeof(unsigned char);
		else
			ptr += m->numIndices * sizeof(unsigned short);
		
		model->sizeIndices += ptr - ((unsigned char *)m->iBuffer);
		if(((ptr - model->data) % 4) > 0)
			model->sizeIndices += 4 - ((ptr - model->data) % 4);
		
		if(m->vBufferType == VertexBufferType::Pos4D)
		{
			//skip indices alignment
			if(m->numIndices % 2 == 1)
				ptr += sizeof(unsigned short);
			//skip normals
			ptr += (m->numIndices / 3) * sizeof(Vector3);
			//skip edges
			const unsigned int *const numEdges = (const unsigned int *const) ptr;
			ptr += sizeof(unsigned int) + ((*numEdges) * sizeof(ShadowVolumes::Caster::Edge));
		}
		
		m->texture = NULL;
		m->name = (char *) ptr;
		m->searchCtrl = GenerateSearchCtrl(m->name);
		ptr += strlen(m->name) + 1;
	}
	
	//if(loadTextures)
	//	model->LoadTextures(filter, wrap);
	
	return model;
#undef ALIGN_4BYTES
}

Model * Model::CreateEmpty()
{
	Model *model = new Model;
	model->data = NULL;
	model->path = NULL;
	model->textureName = NULL;
	model->searchCtrl = GenerateSearchCtrl(model->path);
	
	model->numMeshes = 0;
	model->boundsBox.center = Vector3::Zero;
	model->boundsBox.offset = Vector3::Zero;
	model->boundsSphere.center = Vector3::Zero;
	model->boundsSphere.radius = 0.f;
	model->sizeVertices = 0;
	model->sizeIndices = 0;
	model->meshes = NULL;
	model->buffer = NULL;
	
	return model;
}



void Model::LoadTextures(void)
{
#ifndef _DEDICATED_SERVER
	unsigned char *ptr = data + (sizeof(unsigned int) + sizeof(unsigned int) + sizeof(BoundingBox) + sizeof(BoundingSphere));
	char folder[512];
	strcpy(folder, path);
	char* lastSlash = strrchr(folder, '/');
	if (lastSlash)
		*(lastSlash+1) = 0;
	else
		folder[0] = 0;
	
	for(Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		if(*ptr != '\0')
		{
			char tmp[512];
			sprintf(tmp, "%s%s", folder, (char *) ptr);
			m->texture = Texture2D::Load(tmp, filter, wrap);
			while(*ptr != '\0') ++ptr;
		}
		++ptr;
	}
	
	if(buffer)
		for(Mesh *m = meshes, *mb = buffer->meshes, *end = m + numMeshes; m < end; ++m, ++mb)
			mb->texture = m->texture;
#endif
}

void Model::Render(const Matrix *const World) const
{
#ifndef _DEDICATED_SERVER
	if(buffer)
	{
		Graphics::Instance->SetBufferObject(VBOAllModels);
		Graphics::Instance->SetBufferObject(IBOAllModels);
		Matrix mat;
		for (const Mesh *m = buffer->meshes, *const end = m + numMeshes; m < end; ++m)
		{
			Matrix::Multiply(World, &m->transform, &mat);
			Graphics::Instance->SetWorld(&mat);
			if(m->texture)
				Graphics::Instance->Texture = m->texture;
			m->Draw();
		}
	}
	else
	{
		Matrix mat;
		for (const Mesh *m = meshes, *const end = m + numMeshes; m < end; ++m)
		{
			Matrix::Multiply(World, &m->transform, &mat);
			Graphics::Instance->SetWorld(&mat);
			if(m->texture)
				Graphics::Instance->Texture = m->texture;
			m->Draw();
		}
	}
#endif
}

float Mesh::IntersectsRay(const Vector3& ro, const Vector3& rd, Vector3* ip)
{
	float dist = 100000.0f;
	VertexPosNormalTex* verts = (VertexPosNormalTex*) vBuffer;
	unsigned short* inds = (unsigned short*) iBuffer;


	if (drawMode == DrawMode::TriangleList)
	{
		for (int i=0; i<numIndices; i+=3)
		{
			Vector3 p;
			float d = IntersectsTri(ro, rd, verts[inds[i]].pos, verts[inds[i+1]].pos, verts[inds[i+2]].pos, &p);

			if (d < dist)
			{
				dist = d;
				*ip = p;
			}
		}
	}

	if (dist > 99999.0f)
		return -1;

	return dist;
}

float Mesh::IntersectsTri(const Vector3& ro, const Vector3& rd, const Vector3& p1, const Vector3& p2, const Vector3& p3, Vector3* ip)
{
	Vector3 u = p2-p1;
	Vector3 v = p3-p1;
	Vector3 n = u * v;

	//verifica triunghiuri degenerate
	if (n.LengthSquared() < 0.0001f)
		return -1.0f;

	Vector3 w0 = ro - p1;
	float a = Vector3::Dot(&n, &w0);
	float b = Vector3::Dot(&n, &rd);

	if (Math::Abs(b) < 0.0000001f)
	{
		if (a == 0.0f)
			return 0.0f;	//sunt exact in planul triunghiului

		return -1.0f;	//pe la spate, pe la spate
	}

	float r = a / b;
	if (r <= 0.0f)
		return r;  //ma uit in partea cealalta

	*ip = ro + rd*r;	//punctul de intersectie


	//calculeaza unghiurile exterioare
	float uu = Vector3::Dot(&u, &u);
	float uv = Vector3::Dot(&u, &v);
	float vv = Vector3::Dot(&v, &v);

	//calculeaza unghiurile interioare
	Vector3 w = *ip - p1;
	float wu = Vector3::Dot(&w, &u);
	float wv = Vector3::Dot(&w, &v);

	float D = uv * uv - uu * vv;

	//magie sau ceva, nu prea inteleg :)
	float s = (uv * wv - vv * wu) / D;
	if ((s < 0.0f) || (s > 1.0f))
		return -1.0f;

	float t = (uv * wu - uu - wv) / D;
	if ((t < 0.0f) || (t > 1.0f))
		return -1.0f;

	//ar trebui sa fie inauntru...
	return r;
}
