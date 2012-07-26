
#include "TankIncludes.h"

bool Intersection::SphereSphere(const Vector3 *const pos1, const float _rad1, const Vector3 *const pos2, const float _rad2)
{
	Vector3 l = *pos2 - *pos1;
	float dst2 = Vector3::Dot(&l, &l);
	float mindst = _rad1 + _rad2;
	
	return (dst2 <= mindst * mindst);
}

bool Intersection::SphereSphere(const Vector3 *const pos, const float rad, const BoundingSphere *const sphere)
{
	Vector3 l = sphere->center - *pos;
	float dst2 = Vector3::Dot(&l, &l);
	float mindst = rad + sphere->radius;
	
	return (dst2 <= mindst * mindst);
}

bool Intersection::SphereSphere(const BoundingSphere *const sphere0, const BoundingSphere *const sphere1)
{
	Vector3 l = sphere1->center - sphere0->center;
	float dst2 = Vector3::Dot(&l, &l);
	float mindst = sphere0->radius + sphere1->radius;
	
	return (dst2 <= mindst * mindst);
}

bool Intersection::SphereBox(const Vector3 * const spherePos, const float rad, const Vector3 * const boxPos, const BoundingBox *box)
{
	Vector3 p1, p2;
	p1 = *boxPos + box->center - box->offset;
	p1 -= rad;
	p2 = *boxPos + box->center + box->offset;
	p2 += rad;

	// x test
	if (spherePos->x < p1.x || spherePos->x > p2.x)
		return false;
	
	// y test
	if (spherePos->y < p1.y || spherePos->y > p2.y)
		return false;
	
	// z test
	if (spherePos->z < p1.z || spherePos->z > p2.z)
		return false;
	
	return true;
}

bool Intersection::SphereOrientedBox(const Vector3 *const spherePos, const float rad,const  Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat,const float scale)
{
	Vector3 loc, relloc, p1, p2;
	
	relloc = *spherePos - *boxPos;
	
	loc.x = Vector3::Dot( &relloc, &mat->Right() );
	loc.y = Vector3::Dot( &relloc, &mat->Up() );
	loc.z = Vector3::Dot( &relloc, &-mat->Backward() );
	
	p1 = box->center - box->offset * scale;
	p1 -= rad;
	p2 = box->center + box->offset * scale;
	p2 += rad;
	
	// x test
	if (loc.x < p1.x || loc.x > p2.x)
		return false;
	
	// y test
	if (loc.y < p1.y || loc.y > p2.y)
		return false;
	
	// z test
	if (loc.z < p1.z || loc.z > p2.z)
		return false;
	
	return true;
}

bool Intersection::SphereOrientedBox(const BoundingSphere *const sphere, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat,const float scale)
{
	Vector3 loc, relloc, p1, p2;
	
	relloc = sphere->center - *boxPos;
	
	loc.x = Vector3::Dot( &relloc, &mat->Right() );
	loc.y = Vector3::Dot( &relloc, &mat->Up() );
	loc.z = Vector3::Dot( &relloc, &-mat->Backward() );
	
	p1 = box->center - box->offset * scale;
	p1 -= sphere->radius;
	p2 = box->center + box->offset * scale;
	p2 += sphere->radius;
	
	// x test
	if (loc.x < p1.x || loc.x > p2.x)
		return false;
	
	// y test
	if (loc.y < p1.y || loc.y > p2.y)
		return false;
	
	// z test
	if (loc.z < p1.z || loc.z > p2.z)
		return false;
	
	return true;
}

bool Intersection::PointSphere(const Vector3 *const pos, const Vector3 *const spherePos, const float sphereRadius)
{
	Vector3 l = *spherePos - *pos;
	float dst2 = Vector3::Dot(&l, &l);
	
	return (dst2 <= sphereRadius * sphereRadius);
}

bool Intersection::PointSphere(const Vector3 *const pos, const BoundingSphere *const sphere)
{
	Vector3 l = sphere->center - *pos;
	float dst2 = Vector3::Dot(&l, &l);
	
	return (dst2 <= sphere->radius * sphere->radius);
}

bool Intersection::PointBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box)
{
	Vector3 p1, p2;
	p1 = *boxPos + box->center - box->offset;
	p2 = *boxPos + box->center + box->offset;
	
	// x test
	if (pos->x < p1.x || pos->x > p2.x)
		return false;
	
	// y test
	if (pos->y < p1.y || pos->y > p2.y)
		return false;
	
	// z test
	if (pos->z < p1.z || pos->z > p2.z)
		return false;
	
	return true;
}

bool Intersection::PointOrientedBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat)
{
	Vector3 loc, relloc, p1, p2;
	
	relloc = *pos - *boxPos;
	
	loc.x = Vector3::Dot( &relloc, &mat->Right() );
	loc.y = Vector3::Dot( &relloc, &mat->Up() );
	loc.z = Vector3::Dot( &relloc, &-mat->Backward() );
	
	p1 = box->center - box->offset;
	p2 = box->center + box->offset;
	
	// x test
	if (loc.x < p1.x || loc.x > p2.x)
		return false;
	
	// y test
	if (loc.y < p1.y || loc.y > p2.y)
		return false;
	
	// z test
	if (loc.z < p1.z || loc.z > p2.z)
		return false;
	
	return true;
}


/*

bool GameMode::IntersectSphereBoudingBox(const Vector3 *tsphere,float radius,Target* tbBox)
{
	if (!tsphere || !tbBox || !tbBox->targetModel)
		return false;

	//transform the bounding box;
	Matrix minv;
	Vector3 vecMS;
	if (!tbBox->cacheInverseMat) //cacheInverseMat is used for objects that never move. TODO This inverse should be done just once per frame if needed. 
	{
		Matrix::Invert(tbBox->GetMatPtr(),&minv);
		Vector3::Transform(tsphere,&minv,&vecMS);	
	}
	else
	{
		Vector3::Transform(tsphere,tbBox->GetMatInvPtr(),&vecMS);	

	}
	return Intersection::SphereBox(&vecMS,radius,&Vector3::Zero,&tbBox->targetModel->boundsBox);


}

bool GameMode::IntersectPointBoudingBox(const Vector3 *tpoint,Target* tbBox,Matrix* mat)
{
	if (!tpoint || !tbBox || !tbBox->targetModel)
		return false;

	//transform the bounding box;
	Matrix minv;
	Vector3 vecMS;
	//	Matrix tmp = tbBox->GetMat();
	//	tmp.Translation().y += tbBox->targetModel->boundsBox.center.y;


	if (mat == NULL)
		Matrix::Invert(tbBox->GetMatPtr(),&minv);
	else
		Matrix::Invert(mat,&minv);


	Vector3::Transform(tpoint,&minv,&vecMS);
	return Intersection::PointBox(&vecMS,&Vector3::Zero,&tbBox->targetModel->boundsBox);


}
*/
bool GameIntersection::SphereOrientedBox(const Vector3 *const spherePos, const float rad, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat, const float scale)
{
	Matrix M;
	M = *mat;
	M.Translation() = *boxPos;
	M.Scale(scale);
	M.Invert();

	Vector3 newpos;
	Vector3::Transform(spherePos,&M,&newpos);
	float newrad = rad * scale;

	return Intersection::SphereBox(&newpos,newrad,&Vector3::Zero,box);
}
/*

bool GameIntersection::PointOrientedBox(const Vector3 *const pos, const Vector3 *const boxPos, const BoundingBox *const box, const Matrix *const mat)
{

	Matrix minv;
	Vector3 vecMS;

	Matrix M;
	M = *mat;
	M.Translation() = *boxPos;
	M.Invert();

	Vector3 newpos;
	Vector3::Transform(pos,&M,&newpos);

	return Intersection::PointBox(&newpos,&Vector3::Zero,box);
}

bool GameIntersection::Box3Box3(BaseObject *O1,BaseObject *O2)
{
	if (O1 == NULL)
	{
		return false;
	}
	if (O2 == NULL)
	{
		return false;
	}
	if (O1->model == NULL)
	{
		return false;
	}
	if (O2->model == NULL)
	{
		return false;
	}
	Vector3 SphereCenter1 = O1->model->BoundSphere.center + O1->pos;
	Vector3 SphereCenter2 = O2->model->BoundSphere.center + O2->pos;
	float SphereRadius1 = O1->model->BoundSphere.radius;
	float SphereRadius2 = O2->model->BoundSphere.radius;
	if ((SphereCenter1 - SphereCenter2).Length() > (SphereRadius1 + SphereRadius2))
	{
		//return false;
	}

	Vector3 SphereCenter;
	Matrix Mat;

	SphereCenter = O2->model->BoundSphere.center + O2->pos;
	Matrix::CreateFromQuaternion(&O1->orient,&Mat);
	if (!GameIntersection::SphereOrientedBox(&SphereCenter,O2->model->BoundSphere.radius,&O1->pos,&O1->model->BoundBox,&Mat,1.0))
	{
		return false;
	}

	SphereCenter = O1->model->BoundSphere.center + O1->pos;
	Matrix::CreateFromQuaternion(&O2->orient,&Mat);
	if (!GameIntersection::SphereOrientedBox(&SphereCenter,O1->model->BoundSphere.radius,&O2->pos,&O2->model->BoundBox,&Mat,1.0))
	{
		return false;
	}



	Vector3 BoxPos;
	Vector3 Point;
	Vector3 Delta;
	Vector3 DX,DY,DZ;

	Matrix M1,M2;
	Matrix::CreateFromQuaternion(&O1->orient,&M1);
	Matrix::CreateFromQuaternion(&O2->orient,&M2);
	
	
	BoxPos = O1->pos;
	Delta = O1->model->BoundBox.offset;
	DX.Set(Delta.x,0.0,0.0);
	DY.Set(0.0,Delta.y,0.0);
	DZ.Set(0.0,0.0,Delta.z);

	Point = M1 * (O1->model->BoundBox.center - DX - DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center + DX - DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center - DX + DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center + DX + DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center - DX - DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center + DX - DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center - DX + DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}

	Point = M1 * (O1->model->BoundBox.center + DX + DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O2->pos,&O2->model->BoundBox,&M2))
	{
		return true;
	}



	BoxPos = O2->pos;
	Delta = O2->model->BoundBox.offset;
	DX.Set(Delta.x,0.0,0.0);
	DY.Set(0.0,Delta.y,0.0);
	DZ.Set(0.0,0.0,Delta.z);	   

	Point = M2 * (O2->model->BoundBox.center - DX - DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center + DX - DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center - DX + DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center + DX + DY - DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center - DX - DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center + DX - DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center - DX + DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	Point = M2 * (O2->model->BoundBox.center + DX + DY + DZ) + BoxPos;
	if (GameIntersection::PointOrientedBox(&Point,&O1->pos,&O1->model->BoundBox,&M1))
	{
		return true;
	}

	return false;
}
*/

bool GameIntersection::Box3Box3(BaseObject *O1,BaseObject *O2)
{
	if (O1 == NULL)
	{
		return false;
	}
	if (O2 == NULL)
	{
		return false;
	}
	if (O1->model == NULL)
	{
		return false;
	}
	if (O2->model == NULL)
	{
		return false;
	}
/*	Vector3 SphereCenter1 = O1->model->BoundSphere.center + O1->pos;
	Vector3 SphereCenter2 = O2->model->BoundSphere.center + O2->pos;
	float SphereRadius1 = O1->model->BoundSphere.radius;
	float SphereRadius2 = O2->model->BoundSphere.radius;
	if ((SphereCenter1 - SphereCenter2).Length() > (SphereRadius1 + SphereRadius2))
	{
		//return false;
	}

	Vector3 SphereCenter;
	Matrix Mat;

	SphereCenter = O2->model->BoundSphere.center + O2->pos;
	Matrix::CreateFromQuaternion(&O1->orient,&Mat);
	if (!GameIntersection::SphereOrientedBox(&SphereCenter,O2->model->BoundSphere.radius,&O1->pos,&O1->model->BoundBox,&Mat,1.0))
	{
		//return false;
	}

	SphereCenter = O1->model->BoundSphere.center + O1->pos;
	Matrix::CreateFromQuaternion(&O2->orient,&Mat);
	if (!GameIntersection::SphereOrientedBox(&SphereCenter,O1->model->BoundSphere.radius,&O2->pos,&O2->model->BoundBox,&Mat,1.0))
	{
		//return false;
	}*/


	Matrix Mat1,Mat2,Mat3,R,AbsR;
	Vector3 t;

//	Matrix::CreateFromQuaternionTranslationScale(&O1->orient,&Vector3::Zero,&O1->scale,&Mat1);
	Matrix::CreateFromQuaternion(&O1->orient,&Mat1);
	Matrix::CreateFromQuaternion(&O2->orient,&Mat2);
//	Matrix::CreateFromQuaternionTranslationScale(&O2->orient,&Vector3::Zero,&O2->scale,&Mat2);

	//Magie
	Mat2.Invert();
	Mat1.Translation() = O1->pos + O1->model->BoundBox.center - O2->pos - O2->model->BoundBox.center;
	R = Mat2 * Mat1;
	t = R.Translation();
	R.Translation().Set(0.0,0.0,0.0);
	t = R * t;

	for (int i = 0;i < 16;i += 1)
	{
		AbsR.Ptr()[i] = Math::Abs(R.Ptr()[i]) + numeric_limits<float>::epsilon();
	}

	BoundingBox B1,B2;
	B1 = O1->model->BoundBox;
	B2 = O2->model->BoundBox;

	B1.center.x *= O1->scale.x;
	B1.center.y *= O1->scale.y;
	B1.center.z *= O1->scale.z;

	B1.offset.x *= O1->scale.x;
	B1.offset.y *= O1->scale.y;
	B1.offset.z *= O1->scale.z;

	B2.center.x *= O2->scale.x;
	B2.center.y *= O2->scale.y;
	B2.center.z *= O2->scale.z;

	B2.offset.x *= O2->scale.x;
	B2.offset.y *= O2->scale.y;
	B2.offset.z *= O2->scale.z;

	float ra, rb; 

	for (int i = 0; i < 3; i++)  
	{ 
		ra = B1.offset.Ptr()[i]; 
		rb = B2.offset.Ptr()[0] * AbsR.Ptr()[i * 4 + 0] + 
			 B2.offset.Ptr()[1] * AbsR.Ptr()[i * 4 + 1] +
		     B2.offset.Ptr()[2] * AbsR.Ptr()[i * 4 + 2];
		ra = Math::Abs(ra);
		rb = Math::Abs(rb);
		if (Math::Abs(t.Ptr()[i]) > ra + rb)  
		{ 
			return false; 
		} 
	} 

	for (int i = 0; i < 3; i++)  
	{ 
		ra = B1.offset.Ptr()[0] * AbsR.Ptr()[0 * 4 + i] + 
			 B1.offset.Ptr()[1] * AbsR.Ptr()[1 * 4 + i] +
			 B1.offset.Ptr()[2] * AbsR.Ptr()[2 * 4 + i];
		rb = B2.offset.Ptr()[i]; 
		ra = Math::Abs(ra);
		rb = Math::Abs(rb);
		if (Math::Abs(t.Ptr()[0] * R.Ptr()[0 * 4 + i] + t.Ptr()[1] * R.Ptr()[1 * 4 + i] + t.Ptr()[2] * R.Ptr()[2 * 4 + i]) > ra + rb)
		{ 
			return false; 
		} 
	}

	ra = B1.offset.Ptr()[1] * AbsR.Ptr()[2 * 4 + 0] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[1 * 4 + 0];
	rb = B2.offset.Ptr()[1] * AbsR.Ptr()[0 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[0 * 4 + 1];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[2] * R.Ptr()[1 * 4 + 0] - t.Ptr()[1] * R.Ptr()[2 * 4 + 0]) > ra + rb)
	{ 
		return false; 
	} 


	ra = B1.offset.Ptr()[1] * AbsR.Ptr()[2 * 4 + 1] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[1 * 4 + 1];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[0 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[0 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[2] * R.Ptr()[1 * 4 + 1] - t.Ptr()[1] * R.Ptr()[2 * 4 + 1]) > ra + rb)
	{ 
		return false; 
	} 

	ra = B1.offset.Ptr()[1] * AbsR.Ptr()[2 * 4 + 2] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[1 * 4 + 2];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[0 * 4 + 1] + 
		B2.offset.Ptr()[1] * AbsR.Ptr()[0 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[2] * R.Ptr()[1 * 4 + 2] - t.Ptr()[1] * R.Ptr()[2 * 4 + 2]) > ra + rb)
	{ 
		return false; 
	} 



	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[2 * 4 + 0] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[0 * 4 + 0];
	rb = B2.offset.Ptr()[1] * AbsR.Ptr()[1 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[1 * 4 + 1];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[0] * R.Ptr()[2 * 4 + 0] - t.Ptr()[2] * R.Ptr()[0 * 4 + 0]) > ra + rb)
	{ 
		return false; 
	} 


	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[2 * 4 + 1] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[0 * 4 + 1];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[1 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[1 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[0] * R.Ptr()[2 * 4 + 1] - t.Ptr()[2] * R.Ptr()[0 * 4 + 1]) > ra + rb)
	{ 
		return false; 
	} 

	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[2 * 4 + 2] + 
		B1.offset.Ptr()[2] * AbsR.Ptr()[0 * 4 + 2];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[1 * 4 + 1] + 
		B2.offset.Ptr()[1] * AbsR.Ptr()[1 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[0] * R.Ptr()[2 * 4 + 2] - t.Ptr()[2] * R.Ptr()[0 * 4 + 2]) > ra + rb)
	{ 
		return false; 
	} 


	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[1 * 4 + 0] + 
		B1.offset.Ptr()[1] * AbsR.Ptr()[0 * 4 + 0];
	rb = B2.offset.Ptr()[1] * AbsR.Ptr()[2 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[2 * 4 + 1];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[1] * R.Ptr()[0 * 4 + 0] - t.Ptr()[0] * R.Ptr()[1 * 4 + 0]) > ra + rb)
	{ 
		return false; 
	} 

	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[1 * 4 + 1] + 
		B1.offset.Ptr()[1] * AbsR.Ptr()[0 * 4 + 1];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[2 * 4 + 2] + 
		B2.offset.Ptr()[2] * AbsR.Ptr()[2 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[1] * R.Ptr()[0 * 4 + 1] - t.Ptr()[0] * R.Ptr()[1 * 4 + 1]) > ra + rb)
	{ 
		return false; 
	} 

	ra = B1.offset.Ptr()[0] * AbsR.Ptr()[1 * 4 + 2] + 
		B1.offset.Ptr()[1] * AbsR.Ptr()[0 * 4 + 2];
	rb = B2.offset.Ptr()[0] * AbsR.Ptr()[2 * 4 + 1] + 
		B2.offset.Ptr()[1] * AbsR.Ptr()[2 * 4 + 0];
	ra = Math::Abs(ra);
	rb = Math::Abs(rb);
	if (Math::Abs(t.Ptr()[1] * R.Ptr()[0 * 4 + 2] - t.Ptr()[0] * R.Ptr()[1 * 4 + 2]) > ra + rb)
	{ 
		return false; 
	} 

	return true;

}

float GameIntersection::RayBox3(BoundingBox &BB,Quaternion &orient,Vector3 &Pos,Vector3 &Scale,Vector3 &RayStart,Vector3 &RayEnd)
{
	float x1,x2,y1,y2,z1,z2;

	x1 = BB.center.x - BB.offset.x;
	x2 = BB.center.x + BB.offset.x;

	y1 = BB.center.y - BB.offset.y;
	y2 = BB.center.y + BB.offset.y;

	z1 = BB.center.z - BB.offset.z;
	z2 = BB.center.z + BB.offset.z;

	if (x1 > x2)
	{
		float t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		float t = y1;
		y1 = y2;
		y2 = t;
	}
	if (z1 > z2)
	{
		float t = z1;
		z1 = z2;
		z2 = t;
	}

	Matrix Inv;
	Matrix::CreateFromQuaternionTranslationScale(&orient,&Pos,&Scale,&Inv);
	Inv.Invert();


	Vector3 O,D;

	Vector3::Transform(&RayStart,&Inv,&O);
	Vector3::Transform(&RayEnd,&Inv,&D);

	if (((D.x < x1) && (O.x < x1)) || ((D.x > x2) && (O.x > x2)))
	{
		return -1.0;
	}
	if (((D.y < y1) && (O.y < y1)) || ((D.y > y2) && (O.y > y2)))
	{
		return -1.0;
	}
	if (((D.z < z1) && (O.z < z1)) || ((D.z > z2) && (O.z > z2)))
	{
		return -1.0;
	}

	D = D - O;

	float t;
	float tmin1,tmax1;
	float tmin2,tmax2;
	float tmin3,tmax3;

	float tminf,tmaxf;

	tmin1 = (x1 - O.x) / D.x;
	tmax1 = (x2 - O.x) / D.x;
	if (tmin1 > tmax1)
	{
		t = tmin1;
		tmin1 = tmax1;
		tmax1 = t;
	}

	tmin2 = (y1 - O.y) / D.y;
	tmax2 = (y2 - O.y) / D.y;
	if (tmin2 > tmax2)
	{
		t = tmin2;
		tmin2 = tmax2;
		tmax2 = t;
	}

	tmin3 = (z1 - O.z) / D.z;
	tmax3 = (z2 - O.z) / D.z;
	if (tmin3 > tmax3)
	{
		t = tmin3;
		tmin3 = tmax3;
		tmax3 = t;
	}

	tminf = 0.0;
	tmaxf = 1.0;


	if ((tminf > tmax1) || (tmaxf < tmin1))
	{
		return -1.0;
	}
	tminf = Math::Max(tminf,tmin1);
	tmaxf = Math::Min(tmaxf,tmax1);


	if ((tminf > tmax2) || (tmaxf < tmin2))
	{
		return -1.0;
	}
	tminf = Math::Max(tminf,tmin2);
	tmaxf = Math::Min(tmaxf,tmax2);

	if ((tminf > tmax3) || (tmaxf < tmin3))
	{
		return -1.0;
	}
	tminf = Math::Max(tminf,tmin3);
	tmaxf = Math::Min(tmaxf,tmax3);

	if (tminf > 1.0)
	{
		return -1.0;
	}

	return tminf;
}

float GameIntersection::RayBox3NoY(BoundingBox &BB,Quaternion &orient,Vector3 &Pos,Vector3 &Scale,Vector3 &RayStart,Vector3 &RayEnd)
{
/*	BB.center.Set(0.0,0.0,0.0);
	BB.offset.Set(1.0,1.0,1.0);
	orient = Quaternion::Identity;
	Pos.Set(0.0,0.0,0.0);
	Scale.Set(1.0,1.0,1.0);
	RayStart.Set(1.0,0.0,2.0);
	RayEnd.Set(-1.0,0.0,2.0);*/

	float x1,x2,z1,z2;

	x1 = BB.center.x - BB.offset.x;
	x2 = BB.center.x + BB.offset.x;

	z1 = BB.center.z - BB.offset.z;
	z2 = BB.center.z + BB.offset.z;

	if (x1 > x2)
	{
		float t = x1;
		x1 = x2;
		x2 = t;
	}
	if (z1 > z2)
	{
		float t = z1;
		z1 = z2;
		z2 = t;
	}

	Matrix Inv;
	Matrix::CreateFromQuaternionTranslationScale(&orient,&Pos,&Scale,&Inv);
	Inv.Invert();


	Vector3 O,D;

	Vector3::Transform(&RayStart,&Inv,&O);
	Vector3::Transform(&RayEnd,&Inv,&D);

	if (((D.x < x1) && (O.x < x1)) || ((D.x > x2) && (O.x > x2)))
	{
		return -1.0;
	}
	if (((D.z < z1) && (O.z < z1)) || ((D.z > z2) && (O.z > z2)))
	{
		return -1.0;
	}

	D = D - O;

	float t;
	float tmin1,tmax1;
	float tmin3,tmax3;

	float tminf,tmaxf;

	tmin1 = (x1 - O.x) / D.x;
	tmax1 = (x2 - O.x) / D.x;
	if (tmin1 > tmax1)
	{
		t = tmin1;
		tmin1 = tmax1;
		tmax1 = t;
	}

	tmin3 = (z1 - O.z) / D.z;
	tmax3 = (z2 - O.z) / D.z;
	if (tmin3 > tmax3)
	{
		t = tmin3;
		tmin3 = tmax3;
		tmax3 = t;
	}

	tminf = 0.0;
	tmaxf = 1.0;


	if ((tminf > tmax1) || (tmaxf < tmin1))
	{
		return -1.0;
	}
	tminf = Math::Max(tminf,tmin1);
	tmaxf = Math::Min(tmaxf,tmax1);


	if ((tminf > tmax3) || (tmaxf < tmin3))
	{
		return -1.0;
	}
	tminf = Math::Max(tminf,tmin3);
	tmaxf = Math::Min(tmaxf,tmax3);

	if (tminf > 1.0)
	{
		return -1.0;
	}

	return tminf;
}

float GameIntersection::RayBox3(BaseObject *O1,Vector3 &RayStart,Vector3 &RayEnd)
{
	return RayBox3(O1->model->BoundBox,O1->orient,O1->pos,O1->scale,RayStart,RayEnd);
}

void Swap(float &f1,float &f2)
{
	float f = f1;
	f1 = f2;
	f2 = f;
}

int GameIntersection::Segment2Segment2(float Ax1,float Az1,float Ax2,float Az2,float Bx1,float Bz1,float Bx2,float Bz2,float &outx,float &outz)
{
	if (Ax1 > Ax2)
	{
		Swap(Ax1,Ax2);
		Swap(Az1,Az2);
	}
	if (Bx1 > Bx2)
	{
		Swap(Bx1,Bx2);
		Swap(Bz1,Bz2);
	}

	int r1ver = 0,r2ver = 0;

	float a1,a2,b1,b2;
	float x;
	float r1,r2;

	a1 = (Az1 - Az2) / (Ax1 - Ax2);
	if (Math::Abs(Ax1 - Ax2) < 1e-10)
	{
		r1ver = 1;
	}
	else
	{
		b1 = Az1 - a1 * Ax1;
	}

	a2 = (Bz1 - Bz2) / (Bx1 - Bx2);
	if (Math::Abs(Bx1 - Bx2) < 1e-10)
	{
		r2ver = 1;
	}
	else
	{
		b2 = Bz1 - a2 * Bx1;
	}

	if (r1ver)
	{
		if (r2ver)
		{
			if ((Ax1 - Bx1) < 1e-10)
			{
				if (Az1 > Az2)
				{
					Swap(Az1,Az2);
				}
				if (Bz1 > Bz2)
				{
					Swap(Bz1,Bz2);
				}
				float i0 = Math::Max(Az1,Bz1);
				float i1 = Math::Min(Az2,Bz2);
				if (i0 <= i1)
				{
					outx = Ax1;
					outz = i0;
					return 1;
				}
			}

			return 0;

		}
		else
		{
			if (Az1 > Az2)
			{
				Swap(Az1,Az2);
			}
			float v = a2 * Ax1 + b2;
			if ((Az1 <= v) && (v <= Az2))
			{
				outx = Ax1;
				outz = v;
				return 1;
			}
			return 0;
		}
	}
	else
	{
		if (r2ver)
		{
			if (Bz1 > Bz2)
			{
				Swap(Bz1,Bz2);
			}
			float v = a1 * Bx1 + b1;
			if ((Bz1 <= v) && (v <= Bz2))
			{
				outx = Bx1;
				outz = v;
				return 1;
			}
			return 0;
		}
		else
		{
			x = (b2 - b1) / (a1 - a2);

			r1 = (x - Ax1) / (Ax2 - Ax1);
			r2 = (x - Bx1) / (Bx2 - Bx1);

			if ((0.0 <= r1) && (r1 <= 1.0))
			{
				if ((0.0 <= r2) && (r2 <= 1.0))
				{
					outx = x;
					outz = a1 * x + b1;
					return 1;
				}
			}

			return 0;
		}
	}

	return -1;
}
