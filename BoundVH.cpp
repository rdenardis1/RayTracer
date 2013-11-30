#include "BoundVH.h"
#include "qsplit.h"

BoundVH::BoundVH(){}
BoundVH::BoundVH(Shape** shapes, int num_shapes)
{
	if (num_shapes ==1) *this = BoundVH(shapes[0], shapes[0]);
	if(num_shapes ==2) *this = BoundVH(shapes[0], shapes[1]);

	//mdpoint of the bounding box
	/*bbox = shapes[0]->boundingBox(0.0f, 0.0f);*/
	bbox = BBox();
	for(int i = 1; i <num_shapes; i++) {
		/*
		bbox = surround(bbox, shapes[i]->boundingBox(0.0f, 0.0f));*/
		bbox = BBox();
	}
	Vector3D pivot = (bbox.max() + bbox.min()) / 2.0f;
	int mid_point = qsplit(shapes, num_shapes, pivot.getX(), 0);

	left = buildBranch(shapes, mid_point, 1);
	right = buildBranch(&shapes[mid_point], num_shapes - mid_point, 1);
}

BBox BoundVH::boundingBox(float time0, float time1) const
{return bbox;}

bool BoundVH::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const
{
	if(!(bbox.rayIntersect(r, tmin, tmax))) return false;

	bool isahit1 = false;
	bool isahit2 = false;
	rec.t = tmax;
	isahit1 = right->hit(r, tmin, tmax, time, rec);
	isahit2 = left->hit(r, tmin, rec.t, time, rec);
	return (isahit1 || isahit2);

}

bool BoundVH::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const
{
	if (!(bbox.rayIntersect(r, tmin, tmax))) return false;

	if(right->shadowHit(r,tmin,tmax, time)) return true;
	return left->shadowHit(r,tmin,tmax, time);
}

Shape* BoundVH::buildBranch(Shape** shapes, int shape_size, int axis)
{
	if(shape_size==1) return shapes[0];
	if(shape_size==2) return new BoundVH(shapes[0], shapes[1]);

	/*BBox box = shapes[0]->boundingBox(0.0f, 0.0f);
	for(int i=1; i< shape_size; i++)
		box = surround(box, shapes[i]->boundingBox(0.0f, 0.0f));*/
	BBox box = BBox();

	Vector3D pivot = (box.max() + box.min())/2.0f;

	int mid_point = qsplit(shapes, shape_size, pivot[axis], axis);

	Shape* left = buildBranch(shapes, mid_point, (axis+1)%3);
	Shape* right = buildBranch(&shapes[mid_point], shape_size-mid_point, (axis+1)%3);
	return new BoundVH(left, right, box);
}

