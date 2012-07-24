const unsigned Model::Version =	('g' << 0) |
								('l' << 8) |
								('m' << 16) |
								(2 << 24);

class Edge
{
public:
    unsigned short index[2];
    unsigned short triangle[2];
    
    Edge()
    {
        index[0] = 0xFFFF;
        index[1] = 0xFFFF;
        triangle[0] = 0xFFFF;
        triangle[1] = 0xFFFF;
    }
};

const unsigned char IndexBufferType::UnsignedByte				= 0x00;
const unsigned char IndexBufferType::UnsignedShort				= 0x01;

const unsigned char VertexBufferType::Pos						= 0x00;
//const unsigned char VertexBufferType::PosColor				= 0x01;
const unsigned char VertexBufferType::PosTex					= 0x02;
const unsigned char VertexBufferType::PosNormalTex				= 0x03;
//const unsigned char VertexBufferType::PosColorTex				= 0x04;
//const unsigned char VertexBufferType::PosNormalColorTex		= 0x05;
//const unsigned char VertexBufferType::PosNormalColorDualTex	= 0x06;
//const unsigned char VertexBufferType::PosDualTex				= 0x07;
//const unsigned char VertexBufferType::Pos2D					= 0x08;
//const unsigned char VertexBufferType::Pos2DColor				= 0x09;
//const unsigned char VertexBufferType::Pos2DTex				= 0x0A;
//const unsigned char VertexBufferType::Pos2DColorTex			= 0x0B;
const unsigned char VertexBufferType::Pos4D						= 0x0C;

Model * Model::Load(const char *const file, const bool loadTextures)
{
#define ALIGN_4BYTES	{tmp = (ptr - model->data) % 4; if(tmp > 0) { ptr += (4 - tmp); }}
	Model *model = Find(file);
	if(model)		return model;

	FileStream *fs = FileStream::Open(file);
	if(fs == NULL)	return NULL;
	
	unsigned char *ptr = new unsigned char[fs->size];
	fs->Read(ptr, fs->size);
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
	
	for(unsigned i = 0; i < model->numMeshes; ++i)
	{
		while (*ptr != '\0') ++ptr;
		++ptr;
	}
	
	ALIGN_4BYTES
	
	model->meshes = (Mesh *) ptr;								ptr += model->numMeshes * sizeof(Mesh);
	
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
		m->iBuffer = ptr;
		if(m->iBufferType == IndexBufferType::UnsignedByte)
			ptr += m->numIndices * sizeof(unsigned char);
		else
			ptr += m->numIndices * sizeof(unsigned short);
        
        if(m->vBufferType == VertexBufferType::Pos4D)
        {
            //skip indices alignment
            if(m->numIndices % 2 == 1)
                ptr += sizeof(unsigned short);
            
            //skip normals
            ptr += (m->numIndices / 3) * sizeof(Vector3);
            
            //skip edges
            unsigned int *numEdges = (unsigned int *) ptr;
            ptr += sizeof(unsigned int) + ((*numEdges) * sizeof(Edge));
        }
		
		m->texture = NULL;
		m->name = (char *) ptr;
		m->searchCtrl = GenerateSearchCtrl(m->name);
		ptr += strlen(m->name) + 1;
	}
	
	if(loadTextures)
		model->LoadTextures();
	
	return model;
#undef ALIGN_4BYTES
}

void Model::LoadTextures()
{	
	unsigned char *ptr = data + (sizeof(unsigned int) + sizeof(unsigned int) + sizeof(BoundingBox) + sizeof(BoundingSphere));
	
	for(Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		m->texture = Texture2D::Load((char *) ptr, FilterState::Linear, WrapState::Clamp);
		while(*ptr != '\0') ++ptr;
		++ptr;
	}
}

void Model::Save(const char *file) const
{
#define ALIGN_4BYTES	{tmp = size % 4; if(tmp > 0) { fs->Write(&tmp, 4 - tmp); size += 4 - tmp; }}
	unsigned int size = 0, tmp;
	FileStream *fs = FileStream::OpenW(file);
	
	fs->Write(&Version,			sizeof(unsigned int));	size += sizeof(unsigned int);
	fs->Write(&numMeshes,		sizeof(unsigned int));	size += sizeof(unsigned int);
	fs->Write(&boundsBox,		sizeof(BoundingBox));	size += sizeof(BoundingBox);
	fs->Write(&boundsSphere,	sizeof(BoundingSphere));size += sizeof(BoundingSphere);
	
	//textures for each mesh
	for (Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		fs->Write(m->texture, strlen((char *) m->texture) + 1); size += strlen((char *) m->texture) + 1;
	}
	
	ALIGN_4BYTES
	
	//meshes info
	for (Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		fs->Write(m, sizeof(Mesh));	size += sizeof(Mesh);
	}
	
	//meshes buffers
	for (Mesh *m = meshes, *end = m + numMeshes; m < end; ++m)
	{
		ALIGN_4BYTES
		switch (m->vBufferType)
		{
			case VertexBufferType::Pos:
				fs->Write(m->vBuffer, m->numVertices * sizeof(VertexPos));			size += m->numVertices * sizeof(VertexPos);
				break;
				//case VertexBufferType::PosColor:			
			case VertexBufferType::PosTex:
				fs->Write(m->vBuffer, m->numVertices * sizeof(VertexPosTex));		size += m->numVertices * sizeof(VertexPosTex);
				break;
			case VertexBufferType::PosNormalTex:
				fs->Write(m->vBuffer, m->numVertices * sizeof(VertexPosNormalTex));	size += m->numVertices * sizeof(VertexPosNormalTex);
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
				fs->Write(m->vBuffer, m->numVertices * sizeof(VertexPos4D));        size += m->numVertices * sizeof(VertexPos4D);
				break;
		}
		if(m->iBufferType == IndexBufferType::UnsignedByte)
		{
			fs->Write(m->iBuffer, m->numIndices * sizeof(unsigned char));			size += m->numIndices * sizeof(unsigned char); 
		}
		else
		{
			fs->Write(m->iBuffer, m->numIndices * sizeof(unsigned short));			size += m->numIndices * sizeof(unsigned short);
		}
        
        if(m->vBufferType == VertexBufferType::Pos4D)
        {
            unsigned int size_indices = (m->numIndices % 2 == 0) ? (m->numIndices * sizeof(unsigned short)) : ((m->numIndices + 1) * sizeof(unsigned short));
            if(m->numIndices % 2 == 1)
            {
                fs->Write(&size_indices, sizeof(unsigned short));                   size += sizeof(unsigned short);
            }
            
            unsigned char *buf = ((unsigned char *) m->iBuffer) + size_indices;
            fs->Write(buf, (m->numIndices / 3) * sizeof(Vector3));                  size += (m->numIndices / 3) * sizeof(Vector3);
            buf += (m->numIndices / 3) * sizeof(Vector3);
            unsigned int *numEdges = (unsigned int *) buf;
            
            fs->Write(buf, sizeof(unsigned int) + ((*numEdges) * sizeof(Edge)));    size += sizeof(unsigned int) + ((*numEdges) * sizeof(Edge));
            
        }
		fs->Write(m->name, strlen(m->name) + 1); size += strlen(m->name) + 1;
	}
	
	delete fs;
#undef ALIGN_4BYTES
}
