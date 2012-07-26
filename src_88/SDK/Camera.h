
#ifndef CAMERA__H
#define CAMERA__H

#include "TankIncludes.h"

class Camera : public BaseObject
{
private :
	int windowx,windowy;
	Matrix PerspectiveMat;
	Matrix CameraMat;
	int type;
public :
	enum {
		CAMERA_3RDPERSON,
		CAMERA_FREE,
	};
	BaseObject* followObject;
	float ObjectFollowPitch;
	Camera(void);
	~Camera(void);
	void Change(int newtype, BaseObject* follow = NULL);
	void UpdatePosition();
	void UpdateOrient();

	void UpdateWindowData(int wx,int wy);

	void CopyCameraMat(Matrix &To);
	
	void Update(void);
	void Render(void);
};

#endif
