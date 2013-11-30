#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// Adapted from Realistic Ray Tracing
#include <vector>
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "Shape.h"
#include "ColorRGB.h"
#include "SimpleTexture.h"
#include "MarbleTexture.h"
#include "Material.h"

class Sphere : public Shape
{
	public:
		Sphere(const Vector3D& ce, float r,  Material* _material );
	//	BBox boundingBox() const;
		bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const;
		bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;
		void printOut() const;
	private:
		Vector3D center;
		float radius;
		Material* material;
	
};

#endif //SPHERE_H