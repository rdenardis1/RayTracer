#ifndef BBOX_H
#define BBOX_H

#include "Ray3D.h"

class BBox
{
public:
	BBox() {}
	BBox(const Vector3D& a, const Vector3D& b) { pp[0] = a; pp[1] = b;}
	Vector3D min() const { return pp[0];}
	Vector3D max() const { return pp[1];}
	
	bool rayIntersect(const Ray3D& r, float timin, float tmax) const;

	Vector3D pp[2];
};

inline BBox surround(const BBox& b1, const BBox& b2) {
	return BBox(
		Vector3D(	b1.min().getX() < b2.min().getX() ? b1.min().getX(): b2.min().getX(),
					b1.min().getY() < b2.min().getY() ? b1.min().getY(): b2.min().getY(),
					b1.min().getZ() < b2.min().getZ() ? b1.min().getZ(): b2.min().getZ()),
		Vector3D(	b1.max().getX() < b2.max().getX() ? b1.max().getX(): b2.max().getX(),
					b1.max().getY() < b2.max().getY() ? b1.max().getY(): b2.max().getY(),
					b1.max().getZ() < b2.max().getZ() ? b1.max().getZ(): b2.max().getZ()));
}

inline bool BBox::rayIntersect(const Ray3D & r, float tmin, float tmax) const
{
	float interval_min = tmin;
	float interval_max = tmax;
	
	int posneg = r.posneg[0];
	float t0 = (pp[posneg].getX() - r.data[0].getX()) * r.data[2].getX();
	float t1 = (pp[1-posneg].getX() - r.data[0].getX()) * r.data[2].getX();
	if (t0 > interval_min) interval_min = t0;
	if(t1 < interval_max) interval_max = t1;
	if(interval_min > interval_max) return false;

	posneg = r.posneg[1];
	t0 = (pp[posneg].getY() - r.data[0].getY()) * r.data[2].getY();
	t1 = (pp[1-posneg].getY() - r.data[0].getY()) * r.data[2].getY();
	if (t0 > interval_min) interval_min = t0;
	if(t1 < interval_max) interval_max = t1;
	if(interval_min > interval_max) return false;

	posneg = r.posneg[2];
	t0 = (pp[posneg].getZ() - r.data[0].getZ()) * r.data[2].getZ();
	t1 = (pp[1-posneg].getZ() - r.data[0].getZ()) * r.data[2].getZ();
	if (t0 > interval_min) interval_min = t0;
	if(t1 < interval_max) interval_max = t1;
	if(interval_min > interval_max) return false;

}




#endif