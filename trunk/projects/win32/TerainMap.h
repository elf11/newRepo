
#ifndef TERAINMAP_H
#define TERAINMAP_H

#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"

class TerainMap : public BaseObject
{
private:
	Matrix TerainMapPos;
public :
	VertexPosColor *VertexData;
	unsigned short *IndexData;

	float HeightMap[256][256];

	TerainMap(void);
	void initializeTerainMap(float HeightMap[256][256]);
	void Update(void);
	void Render(void);
};

#endif