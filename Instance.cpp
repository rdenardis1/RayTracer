/*#include "Instance.h"
#include "Matrix.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* _prim): 
	M(trans), N(trans_inverse), prim(_prim) {}

Instance::Instance(Matrix trans, Shape* _prim)
	: M(trans), N(trans), prim(_prim)
{N.invert();}

bool Instance::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const
{
	Vector3D no = transformLoc(N, r.getOrigin());
	Vector3D nd = transformVec(N, r.getDirection());
	Ray3D tray(no, nd);

	if(prim->hit(tray, tmin, tmax, time, rec))
	{
		rec.hit_p = transformLoc(M, rec.hit_p);
		//not sure what to do here:  
		Vector3D normal = transformVec(N.getTranspose(), rec.normal);
		ONB uvw;
		uvw.initFromW(normal);
		//not sure what should actually be done here
		rec.normal = normal;
		return true;
	}
	else return false;
}

bool Instance::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const
{
	Vector3D no = transformLoc(N, r.getOrigin());
	Vector3D nd = transformVec(N, r.getDirection());
	Ray3D tray(no, nd);
	return (prim->shadowHit(tray, tmin, tmax, time));
}
*/