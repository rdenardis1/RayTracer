#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Shape.h"
#include "Material.h"
#include "BBox.h"
#define PARALLEL_EPSILON 0.0000001f

class Parallelogram  : public Shape
{
public:
	Parallelogram(const Vector3D& _base, const Vector3D& _u, const Vector3D& _v, Material* _mptr);

	Parallelogram(const Vector3D& _base, const Vector3D& _u, const Vector3D& _v, const Vector2D& _uv0,
		const Vector2D& _uv1, const Vector2D& _uv2, Material* _mptr);

	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord & rec) const;

	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;

	BBox boundingBox(float time0, float time1) const;

	bool randomPoint(const Vector3D& viewpoint, const Vector2D& seed, float time, 
		Vector3D& light_point, Vector3D& N, float& pdf, ColorRGB& radiance) const;

	Vector3D base;
	Vector3D u;
	Vector3D v;
	Vector3D norm;
	Vector3D unorm; //normalized u offset
	Vector3D vnorm; //normalized v offset

	Vector2D uv0;
	Vector2D uv1;
	Vector2D uv2;

	float _pdf;
	Material* mptr;
};

#endif