
#ifndef __INTERSECTION_H_DEF__
#define __INTERSECTION_H_DEF__

#include "stdinc.h"
#include "RMath.h"

class BaseObject;

class Intersection
{
public:
	static bool SphereSphere(const Vector3 * const pos1, const float _rad1, const Vector3 * const pos2, const float _rad2);
	static bool SphereSphere(const Vector3 * const pos, const float _rad, const BoundingSphere * const sphere);
	static bool SphereSphere(const BoundingSphere * const sphere0, const BoundingSphere * const sphere1);
	static bool SphereBox(const Vector3 * const spherePos, const float rad, const Vector3 *const boxPos, const BoundingBox *const box);
	static bool SphereOrientedBox(const Vector3 *const spherePos, const float rad, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat, const float scale  = 1.f);
	static bool SphereOrientedBox(const BoundingSphere *const sphere, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat, const float scale  = 1.f);
	static bool PointSphere(const Vector3 *const pos, const Vector3 *const spherePos, const float sphereRadius);
	static bool PointSphere(const Vector3 *const pos, const BoundingSphere *const sphere);
	static bool PointBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box);
	static bool PointOrientedBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat);
	
};

class GameIntersection
{
public :
/*	static bool SphereOrientedBox(const Vector3 *const spherePos, const float rad, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat, const float scale  = 1.f);
	static bool PointOrientedBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat);
	static bool Box3Box3(BaseObject *O1,BaseObject *O2);*/
	static bool SphereOrientedBox(const Vector3 *const spherePos, const float rad, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat, const float scale  = 1.f);
	static bool Box3Box3(BaseObject *O1,BaseObject *O2);
	static float RayBox3(BaseObject *O1,Vector3 &RayStart,Vector3 &RayEnd);
	static float RayBox3(BoundingBox &BB,Quaternion &orient,Vector3 &Pos,Vector3 &Scale,Vector3 &RayStart,Vector3 &RayEnd);
	static float RayBox3NoY(BoundingBox &BB,Quaternion &orient,Vector3 &Pos,Vector3 &Scale,Vector3 &RayStart,Vector3 &RayEnd);

	//nu merge tot timpul
	static int Segment2Segment2(float Ax1,float Az1,float Ax2,float Az2,float Bx1,float Bz1,float Bx2,float Bz2,float &outx,float &outz);

};

#endif // __INTERSECTION_H_DEF__
