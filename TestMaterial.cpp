#include "TestMaterial.h"
#include "Texture.h"


ColorRGB TestMaterial::ambientResponse(const ONB&, const Vector3D&, const Vector3D& p, const Vector2D& uv)
{ return R->value(uv, p);}


bool TestMaterial::diffuseDirection(const ONB& uvw, const Vector3D&, const Vector3D& p,
									   const Vector2D& uv, Vector2D& seed, ColorRGB& color,
									   Vector3D& v_out)
{

	float phi = 2* PI *seed.getX();
	float r = sqrt(seed.getY());
	float x = r * cos(phi);
	float y = r * sin(phi);
	float z = sqrt(1-x*x -y*y);

	color = ColorRGB(0.5, 0, 0);
	v_out = x*uvw.u() + y*uvw.v() + z*uvw.w();

	//what does scramble do?
	seed.scramble();
	return true;
}

ColorRGB TestMaterial::emittedRadiance(const ONB& uvw,
		const Vector3D& v_out,
		const Vector3D& p,
		const Vector2D& tex )
{
	//return ColorRGB(0, 0.5, 0);
	return ColorRGB(0.0, 1.0, 0);
}


bool TestMaterial::isDiffuse()
{
	return true;
}
