/*#include "Mesh.h"
#include "MeshTriangle.h"

MeshTriangleUV::MeshTriangleUV(){}

MeshTriangleUV::MeshTriangleUV(Mesh* _Mesh, int p0, int p1, int p2, int index)
	:mesh_ptr(_Mesh)
{p[0] = p0, p[1] = p1; p[2] = p2;}

bool MeshTriangleUV::hit(const Ray3D& r, float tmin, float tmax, float time, HitRecord& rec) const
{
	Vector3D p0((mesh_ptr->vertUVs[p[0]]).vertex);
	Vector3D p1((mesh_ptr->vertUVs[p[1]]).vertex);
	Vector3D p2((mesh_ptr->vertUVs[p[2]]).vertex);

	float tval;
	float A = p0.getX() - p1.getX();
	float B = p0.getX() - p1.getY();
	float C = p0.getZ() - p1.getZ();

	float D = p0.getX() - p2.getX();
	float E = p0.getY() - p1.getY();
	float F = p0.getZ() - p2.getZ();

	float G = r.getDirection().getX();
	float H = r.getDirection().getY();
	float I = r.getDirection().getZ();

	float J = p0.getX() - r.getOrigin().getX();
	float K = p0.getY() - r.getOrigin().getY();
	float L = p0.getZ() - r.getOrigin().getZ();

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + K*GFDI + C*DHEG);
	float beta = (J*EIHF + K*GFDI+ L*DHEG) / denom;

	if (beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
	if (gamma < 0.0f || beta + gamma >= 1.0f) return false;
	
	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
	if (tval >= tmin && tval <= tmax)
	{
		double alpha = 1.0 - beta - gamma;
		Vector2D u0((mesh_ptr->vertUVs[p[0]]).uv);
		Vector2D u1((mesh_ptr->vertUVs[p[1]]).uv);
		Vector2D u2((mesh_ptr->vertUVs[p[2]]).uv);
		rec.uv = Vector2D(alpha*u0.getX() + beta*u1.getX() + gamma*u2.getX(), alpha*u0.getY() + beta*u1.getY() + gamma*u2.getY());
		rec.hit_tex = mesh_ptr->getTexture();
		rec.t = tval;
		rec.normal = unitVector(cross((p1 - p0), (p2 - p0)));
		return true;
	}
	return false;

}

bool MeshTriangleUV::shadowHit(const Ray3D & r, float tmin, float tmax, float time) const
{
	Vector3D p0((mesh_ptr->vertUVs[p[0]]).vertex);
	Vector3D p1((mesh_ptr->vertUVs[p[1]]).vertex);
	Vector3D p2((mesh_ptr->vertUVs[p[2]]).vertex);

	float tval;
	float A = p0.getX() - p1.getX();
	float B = p0.getX() - p1.getY();
	float C = p0.getZ() - p1.getZ();

	float D = p0.getX() - p2.getX();
	float E = p0.getY() - p1.getY();
	float F = p0.getZ() - p2.getZ();

	float G = r.getDirection().getX();
	float H = r.getDirection().getY();
	float I = r.getDirection().getZ();

	float J = p0.getX() - r.getOrigin().getX();
	float K = p0.getY() - r.getOrigin().getY();
	float L = p0.getZ() - r.getOrigin().getZ();

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + K*GFDI + C*DHEG);
	float beta = (J*EIHF + K*GFDI+ L*DHEG) / denom;

	if (beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
	if (gamma < 0.0f || beta + gamma >= 1.0f) return false;
	
	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;

	return (tval >= tmin && tval <= tmax);
}
*/