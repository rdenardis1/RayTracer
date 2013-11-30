#include "UVSphere.h"

UVSphere::UVSphere(const Vector3D& _center, float _radius, Material* _material)
	: center(_center), radius(_radius), material(_material) {}

bool UVSphere::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3D temp = r.getOrigin() - center;

	double a = dotProduct(r.getDirection(), r.getDirection());
	double b = 2*dotProduct(r.getDirection(), temp);
	double c = dotProduct(temp, temp) - radius*radius;

	double disc = b*b -4*a*c;
	//is there some intersection

	if(disc > 0.0) {
		disc = sqrt(disc);
		double t = (-b - disc) / (2.0*a);
		if (t < tmin)
			t = (-b + disc) /(2.0*a);
		if (t < tmin || t > tmax)
			return false;

		record.t = t;
		record.p = record.texp = (r.getOrigin() + t*r.getDirection());
		record.uvw.initFromW((record.p - center) / radius);

		Vector3D n = (record.p - center) / radius;
		float twopi = 6.28318530718f;
		float theta = acos(n.getZ());
		float phi = atan2(n.getY(), n.getX());
		if (phi < 0.0f) phi+= twopi;

		float one_over_2pi = .159154943029f;
		float one_over_pi = .318309886184f;
		float pi = 3.14159;
		record.uv = Vector2D(phi*one_over_2pi, (pi-theta)*one_over_pi);

		record.mat_ptr = material;
		return true;
	}
	return false;
}


bool UVSphere::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const
{

	Vector3D temp = r.getOrigin() - center;

	double a = dotProduct(r.getDirection(), r.getDirection());
	double b = 2*dotProduct(r.getDirection(), temp);
	double c = dotProduct(temp, temp) - radius*radius;

	double disc = b*b -4*a*c;
	//is there some intersection

	if(disc > 0.0) {
		disc = sqrt(disc);
		double t = (-b - disc) / (2.0*a);
		if (t < tmin)
			t = (-b + disc) /(2.0*a);
		if (t < tmin || t > tmax)
			return false;
		return true;
	}
	return false;
}