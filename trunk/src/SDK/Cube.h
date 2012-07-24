
#ifndef CUBE__H
#define CUBE__H

#include "RMath.h"
#include "VertexDeclarations.h"
#include "BaseObject.h"
#include "Renderer.h"

class Cube : public BaseObject
{
private:
	Matrix CubePos;
public :
	VertexPosColor *VertexData;
	unsigned short *IndexData;

	Cube(void);
	void Update(void);
	void Render(void);
};

#endif
