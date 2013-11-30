#ifndef UV_SPHERE_H
#define UV_SPHERE_H

#include "Shape.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "Material.h"

class UVSphere : public Shape
{
public:
	UVSphere(const Vector3D& _center, float _radius, Material* _material);
	//BB
	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;

	Vector3D center;
	float radius;
	Material* material;
};


#endif