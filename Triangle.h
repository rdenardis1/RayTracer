// Adapted from Realistic Ray Tracing
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Vector3D.h"
#include "ColorRGB.h"
#include "Ray3D.h"
#include "Material.h"

class Triangle: public Shape
{
public:
	Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, Material* _material);
	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;

	Vector3D p0;
	Vector3D p1;
	Vector3D p2;

	Material* material;
};

#endif