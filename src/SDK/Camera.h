
#ifndef CAMERA__H
#define CAMERA__H

#include "RMath.h"
#include "Renderer.h"
#include "BaseObject.h"

class Camera : public BaseObject
{
private :
	int windowx,windowy;
	Matrix PerspectiveMat;
	Matrix CameraMat;
public :
	Camera(void);

	void UpdateWindowData(int wx,int wy);
	
	void Update(void);
	void Render(void);
};

#endif
