
#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"
#include "ModelManager.h"

Mesh::Mesh(ModelManager *Manager)
{
	Parent = Manager;
	open = 0;
}

void Mesh::LoadFromFile(char *FileName)
{
	if (open != 0)
	{
		return;
	}

	MeshName = FileName;


}

void Mesh::Draw(void)
{

}

ModelManager::ModelManager(void)
{

}

Mesh * ModelManager::GetMesh(char *FileName)
{
	return 0;
}
