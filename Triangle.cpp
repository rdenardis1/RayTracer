// Adapted from Realistic Ray Tracing
#include "Triangle.h"

Triangle::Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, Material* _material)
	: p0(a), p1(b), p2(c), material(_material) {}

bool Triangle::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& record) const
{
	float tval;
	float A = p0.getX() - p1.getX();
	float B = p0.getY() - p1.getY();
	float C = p0.getZ() - p1.getZ();

	float D = p0.getX() - p2.getX();
	float E = p0.getY() - p2.getY();
	float F = p0.getZ() - p2.getZ();
	
	float G = r.getDirection().getX();
	float H = r.getDirection().getY();
	float I = r.getDirection().getZ();

	float J = p0.getX() - r.getOrigin().getX();
	float K = p0.getY() - r.getOrigin().getY();
	float L = p0.getZ() - r.getOrigin().getZ();

	float EIHF = E*I-H*F;
	float GFDI = G*F-D*I;
	float DHEG = D*H-E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);

	float beta = (J*EIHF + K*GFDI + L*DHEG)/denom;

	if (beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	float gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
	if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
	if (tval >= tmin && tval <= tmax) 
	{
		record.t = tval;
		record.uvw.initFromW(unitVector(cross((p1-p0), (p2-p0))));
		record.mat_ptr = material;
		record.p = record.texp = r.pointAtParameter(tval);
		return true;
	}
	return false;
}

bool Triangle::shadowHit(const Ray3D& r, float tmin, float tmax, float time) const
{
	float tval;
	float A = p0.getX() - p1.getX();
	float B = p0.getY() - p1.getY();
	float C = p0.getZ() - p1.getZ();

	float D = p0.getX() - p2.getX();
	float E = p0.getY() - p2.getY();
	float F = p0.getZ() - p2.getZ();
	
	float G = r.getDirection().getX();
	float H = r.getDirection().getY();
	float I = r.getDirection().getZ();

	float J = p0.getX() - r.getOrigin().getX();
	float K = p0.getY() - r.getOrigin().getY();
	float L = p0.getZ() - r.getOrigin().getZ();

	float EIHF = E*I-H*F;
	float GFDI = G*F-D*I;
	float DHEG = D*H-E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);

	float beta = (J*EIHF + K*GFDI + L*DHEG)/denom;

	if (beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	float gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
	if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;

	return (tval >= tmin && tval <= tmax);
}