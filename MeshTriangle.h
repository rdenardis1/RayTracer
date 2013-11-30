/*#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H
#include "Shape.h"
class Mesh;
class Texture;

class MeshTriangleUV : public Shape {
public:
	MeshTriangleUV();
	MeshTriangleUV(Mesh* _Mesh, int p0, int p1, int p2, int index);
	~MeshTriangleUV();
	bool hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const;
	bool shadowHit(const Ray3D& r, float tmin, float tmax, float time) const;

	int p[3];
	Mesh* mesh_ptr;
};

#endif*/