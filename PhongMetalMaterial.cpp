#include "PhongMetalMaterial.h"
#include "Texture.h"

ColorRGB PhongMetalMaterial::ambientResponse(const ONB&, const Vector3D&, const Vector3D& p, const Vector2D& uv)
{ return R->value(uv, p);}

bool PhongMetalMaterial::specularDirection(const ONB& uvw, const Vector3D& v_in, const Vector3D& p, const Vector2D& uv,
										   Vector2D& seed, ColorRGB& color, Vector3D& v_out)
{
	float phi = 2* PI* seed.getX();
	//the phong exponent is stored in the red value for the texture at that point
	float exponent = phong_exp->value(uv, p).getRed();
	float cosTheta = pow(1-seed.getY(), 1.0/(exponent+1));
	float sinTheta = sqrt(1-cosTheta*cosTheta);
	float x = cos(phi) * sinTheta;
	float y = sin(phi) * sinTheta;
	float z = cosTheta;
	

	ONB basis;
	Vector3D w = v_in - 2*dotProduct(v_in, uvw.w())*uvw.w();
	basis.initFromW(w);

	//color = R->value(uv, p);
	ColorRGB r = R->value(uv, p);
	float c = 1 - (dotProduct(v_in, uvw.w()));
	color = r + (ColorRGB(1, 1, 1) + (-r))*(c*c*c*c*c);
	v_out = x*basis.u() + y*basis.v() + z*basis.w();

	if(exponent <10000) seed.scramble();
	return (dotProduct(v_out, uvw.w()) >0 );
	
}