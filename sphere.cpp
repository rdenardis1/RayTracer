// Adapted from Realistic Ray Tracing
# include "sphere.h"
# include "Point3D.h"
# include "Ray3D.h"
#include "Texture.h"
# include <math.h>
# include <vector>

Sphere::Sphere(const Vector3D& ce, float r, Material* _material):
	center(ce), radius(r), material(_material){}

bool Sphere::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3D d = r.getDirection();
	Vector3D e = r.getOrigin();
	Vector3D c = center;

	Vector3D diff = e-c;
	double a = dotProduct(r.getDirection(), r.getDirection());
	double discriminant = pow((2*dotProduct(d,diff)), 2) - 4*dotProduct(d,d)*( dotProduct(diff,diff) - radius*radius);

	if (discriminant > 0) 
	{
		discriminant = sqrt(discriminant);
		double t = (- (2*(dotProduct(r.getDirection(), diff))) - discriminant) / (2*a);
		if (t < tmin)
			t =  (- (2*(dotProduct(r.getDirection(), diff))) + discriminant) / (2*a);
		if (t<tmin || t > tmax)
			return false;
		// there is a valid hit
		record.t = t;
		record.uvw.initFromW(unitVector(r.getOrigin() + t*r.getDirection() - center));
		record.p = record.texp = r.pointAtParameter(t);
		record.mat_ptr = material;
		return true;
	}
	return false;
}

bool Sphere::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const
{
	Vector3D d = r.getDirection();
	Vector3D e = r.getOrigin();
	Vector3D c = center;

	Vector3D diff = e-c;
	double a = dotProduct(r.getDirection(), r.getDirection());
	double discriminant = pow((2*dotProduct(d,diff)), 2) - 4*dotProduct(d,d)*( dotProduct(diff,diff) - radius*radius);

	if(discriminant > 0) {
				discriminant = sqrt(discriminant);
		double t = (- (2*(dotProduct(r.getDirection(), diff))) - discriminant) / (2*a);
		if (t < tmin)
			t =  (- (2*(dotProduct(r.getDirection(), diff))) + discriminant) / (2*a);
		if (t<tmin || t > tmax)
			return false;
		return true;
	}
	return false;
	
}

void Sphere::printOut () const {
	printf("center is: ");
	center.printOut();
	printf("radius is: %f", radius);
}
