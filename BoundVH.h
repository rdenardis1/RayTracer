#ifndef BVH_H
#define BVH_H

#include "Shape.h"
#include "BBox.h"


class BoundVH : public Shape
{
public:
	BoundVH();
	BoundVH(Shape** surfaces, int num_surfaces);
	BoundVH(Shape* prim1, Shape* prim2);
	BoundVH(Shape* prim1, Shape*prim2, const BBox& _bbox);
	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const;
	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;
	BBox boundingBox(float time0, float time1) const;
	Shape * buildBranch(Shape** surfaces, int num_surfaces, int axis = 0);

	BBox bbox;
	Shape* left;
	Shape* right;
};

inline BoundVH::BoundVH(Shape* prim1, Shape* prim2, const BBox& _bbox) {
	bbox = _bbox;
	left = prim1;
	right = prim2;
}
inline BoundVH::BoundVH(Shape* prim1, Shape* prim2) {
	left = prim1;
	right = prim2;
	/*
	bbox = surround(prim1->boundingBox(0.0f, 0.0f),
					prim2->boundingBox(0.0f, 0.0f));*/
	bbox = surround(BBox(), BBox());
}


#endif