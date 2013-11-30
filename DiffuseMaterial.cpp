#include "DiffuseMaterial.h"
#include "Texture.h"


ColorRGB DiffuseMaterial::ambientResponse(const ONB&, const Vector3D&, const Vector3D& p, const Vector2D& uv)
{ return R->value(uv, p);}

bool DiffuseMaterial::explicitBrdf(const ONB&, const Vector3D&, const Vector3D&, 
								   const Vector3D& p, const Vector2D& uv, ColorRGB& brdf)
{
	float k = .318309886184f; 
	brdf = k * R->value(uv, p);
	return true;
}

bool DiffuseMaterial::diffuseDirection(const ONB& uvw, const Vector3D&, const Vector3D& p,
									   const Vector2D& uv, Vector2D& seed, ColorRGB& color,
									   Vector3D& v_out)
{

	float phi = 2* PI *seed.getX();
	float r = sqrt(seed.getY());
	float x = r * cos(phi);
	float y = r *sin(phi);
	float z = sqrt(1-x*x -y*y);

	color = R->value(uv, p);
	v_out = x*uvw.u() + y*uvw.v() + z*uvw.w();

	//what does scramble do?
	seed.scramble();
	return true;
}

bool DiffuseMaterial::isDiffuse()
{
	return true;
}
