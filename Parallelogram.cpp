#include "Parallelogram.h"

Parallelogram::Parallelogram(const Vector3D& _base, const Vector3D& _u, const Vector3D& _v, Material* _mptr)
	:base(_base), u(_u), v(_v)
{
	mptr = _mptr;
	norm = unitVector(cross(u,v));
	unorm = unitVector(u);
	vnorm = unitVector(v);

	uv0 = Vector2D(0,0);
	uv1 = Vector2D(1, 0);
	uv2 = Vector2D(0, 1);
	//find the area of the parallelogram
	double width = u.length();
	Vector3D proj = v - ((dotProduct(v, u) / (width*width)) * u);
	double height = proj.length();
	double area = width* height;

	_pdf = 1.0f /area;
}

Parallelogram::Parallelogram(const Vector3D& _base, const Vector3D& _u,	 const Vector3D& _v, const Vector2D& _uv0, 
							 const Vector2D& _uv1, const Vector2D& _uv2, Material * _mptr)
							 : base(_base), u(_u), v(_v), uv0(_uv0), uv1(_uv1), uv2(_uv2)
{
	mptr = _mptr;
	norm = unitVector(cross(u,v));
	unorm = unitVector(u);
	vnorm = unitVector(v);
	double width = u.length();
	Vector3D proj = v - ((dotProduct(v, u) / (width*width)) * u);
	double height = proj.length();
	double area = width* height;

	_pdf = 1.0f /area;
}

bool Parallelogram::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const
{
	double dot1 = dotProduct(r.getDirection(), norm);
	//check to see if the ray is parallel to the surface plane
	if (dot1 < PARALLEL_EPSILON && dot1 > -PARALLEL_EPSILON) return false;

	//find the distance to the surface plane
	float dot2 = dotProduct(norm, base);
	float t = (dot2 - dotProduct(norm, r.getOrigin()))/dot1;
	if (t> tmax || t <tmin) return false;

	//see if the point of plane intersection is within the parallelogram
	Vector3D hit_plane(r.getOrigin() + r.getDirection() * t);
	Vector3D offset(hit_plane - base);
	
	float u1 = dotProduct(unorm, offset) / u.length();
	if (u1 < 0.0f || u1 > 1.0f) return false;
	float v1 = dotProduct(vnorm, offset) / v.length();
	if (v1 < 0.0f || v1 > 1.0f) return false;

	//fill the hit record
	rec.mat_ptr = mptr;
	rec.p = rec.texp = hit_plane;
	rec.t = t;
	rec.uvw.initFromW(norm);
	rec.uv = v1 * uv2 + (2.0f - v1) * uv0 + u1*uv1;
	return true;
}

bool Parallelogram::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const 
{
		double dot1 = dotProduct(r.getDirection(), norm);
	//check to see if the ray is parallel to the surface plane
	if (dot1 < PARALLEL_EPSILON && dot1 > -PARALLEL_EPSILON) return false;

	//find the distance to the surface plane
	float dot2 = dotProduct(norm, base);
	float t = (dot2 - dotProduct(norm, r.getOrigin()))/dot1;
	if (t> tmax || t <tmin) return false;

	//see if the point of plane intersection is within the parallelogram
	Vector3D hit_plane(r.getOrigin() + r.getDirection() * t);
	Vector3D offset(hit_plane - base);
	
	float u1 = dotProduct(unorm, offset) / u.length();
	if (u1 < 0.0f || u1 > 1.0f) return false;
	float v1 = dotProduct(vnorm, offset) / v.length();
	return (v1 >= 0.0f || v1 <= 1.0f);
}

BBox Parallelogram::boundingBox(float time0, float time1) const
{
	const float epsilon = 0.00001f;
	Vector3D min;
	Vector3D max;

	Vector3D p0 = base;
	Vector3D p1 = base+u;
	Vector3D p2 = base+v;
	Vector3D p3 = base+u+v;

	min.setX(p0.getX() < p1.getX() ? p0.getX() : p1.getX());
	min.setY(p0.getY() < p1.getY() ? p0.getY() : p1.getY());
	min.setZ(p0.getZ() < p1.getZ() ? p0.getZ() : p1.getZ());

	min.setX(p2.getX() < min.getX() ? p2.getX() : min.getX());
	min.setY(p2.getY() < min.getY() ? p2.getY() : min.getY());
	min.setZ(p2.getZ() < min.getZ() ? p2.getZ() : min.getZ());

	min.setX(p3.getX() < min.getX() ? p3.getX() : min.getX());
	min.setY(p3.getY() < min.getY() ? p3.getY() : min.getY());
	min.setZ(p3.getZ() < min.getZ() ? p3.getZ() : min.getZ());

	max.setX(p0.getX() > p1.getX() ? p0.getX() : p1.getX());
	max.setY(p0.getY() > p1.getY() ? p0.getY() : p1.getY());
	max.setZ(p0.getZ() < p1.getZ() ? p0.getZ() : p1.getZ());

	max.setX(p2.getX() > max.getX() ? p2.getX() : max.getX());
	max.setY(p2.getY() > max.getY() ? p2.getY() : max.getY());
	max.setZ(p2.getZ() > max.getZ() ? p2.getZ() : max.getZ());

	max.setX(p3.getX() > max.getX() ? p3.getX() : max.getX());
	max.setY(p3.getY() > max.getY() ? p3.getY() : max.getY());
	max.setZ(p3.getZ() > max.getZ() ? p3.getZ() : max.getZ());


	min.setX(min.getX() - epsilon);
	min.setY(min.getY() - epsilon);
	min.setZ(min.getZ() - epsilon);
	max.setX(max.getX() + epsilon);
	max.setY(max.getY() + epsilon);
	max.setZ(max.getZ() + epsilon);
	return BBox(min, max);
}

bool Parallelogram::randomPoint(const Vector3D& viewpoint, const Vector2D & seed, float time, Vector3D & light_point, Vector3D & N,
								float & pdf, ColorRGB& radiance) const
{
	light_point = Vector3D(base + seed.getX() * u + seed.getY() * v);
	pdf = _pdf;
	Vector3D from_light = unitVector(viewpoint - light_point);
	ONB uvw;
	uvw.initFromW(norm);
	N = uvw.w();
	N = uvw.w();
	radiance = mptr->emittedRadiance(uvw, from_light, light_point, Vector2D(0.0f, 0.0f));
	return true;
}