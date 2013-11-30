#ifndef INSTANCE_H
#define INSTANCE_H

#include "Shape.h"
#include "Matrix.h"
class Instance : public Shape
{
public: 
	Instance() {}
	~Instance() {}
	Instance(Matrix trans, Matrix trans_inverse, Shape* _prim);
	Instance(Matrix trans, Shape* _prim);
	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const;
	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;

	Matrix M;
	Matrix N;
	Shape* prim;
};

#endif