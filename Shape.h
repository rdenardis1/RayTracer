// Adapted from Realistic Ray Tracing
#ifndef SHAPE_H
#define SHAPE_H

#include "Ray3D.h"
#include "Vector3D.h"
#include "ColorRGB.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ONB.h"
#include "SimpleTexture.h"

class Ray3D;
class ColorRGB;
class SimpleTexture;
class Material;

struct HitRecord
{
	float t;
	Vector2D uv; // can be used for 2D textures
	Vector3D p; //the point of intersection
	Vector3D texp; //point of intersection for texture mapping
	ONB uvw;	// w is the outward normal
	Material* mat_ptr;
};

class Shape
{
	public:
		virtual bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const=0;
		virtual bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const=0;
};

#endif //SHAPE_H