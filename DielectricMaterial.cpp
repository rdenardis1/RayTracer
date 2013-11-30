#include "DielectricMaterial.h"
#include <math.h>

DielectricMaterial::DielectricMaterial(float _nt, const ColorRGB&  _ex)
	: nt(_nt), extinction(_ex)
{
	R0 = (nt - 1.0f) / (nt+ 1.0f);
	R0 *= R0;

	float r = log(extinction.getRed());
	float g = log(extinction.getGreen());
	float b = log(extinction.getBlue());
	extinction = ColorRGB(r,g,b);

}


bool DielectricMaterial::specularDirection(const ONB & uvw,
		const Vector3D& in_dir,		//incident vector
		const Vector3D& texp,		//texture point
		const Vector2D& uv,			//texture coordinate
		Vector2D& rseed,			// random seed
		ColorRGB& ratio,
		Vector3D& reflection)
{
	float scale;
	Vector3D normal = uvw.w();
	float cosine = dotProduct(in_dir, normal);
	if(cosine < 0.0f ) //ray is incoming
	{
		//reflection = reflect(in_dir, uvw.w());
		reflection = Vector3D();
		cosine = -cosine;
		float temp1 = 1.0f - cosine;
		scale = R0 + (1.0f - R0) *temp1*temp1*temp1*temp1*temp1;
	}
	else
	{
		//reflection = reflect(in_dir, -uvw.w());
		reflection = Vector3D();
		float temp2 = -(dotProduct(in_dir, -normal));
		float root = 1.0f - (nt*nt) *(1.0f-temp2 *temp2);
		if (root < 0.0f) scale = 1.0f;
		else {
			float temp3 = 1.0f - cosine;
			scale = R0 + (1.0f - R0) * temp3*temp3*temp3*temp3*temp3;
		}
	}
	ratio = ColorRGB(scale, scale, scale);
	return true;
}

bool DielectricMaterial::transmissionDirection(const ONB& uvw,
		const Vector3D& in_dir,		//incident unit vector
		const Vector3D& texp,		//texture point
		const Vector2D& uv,			//texture coordinate
		const Vector2D& rseed,		// random seed
		ColorRGB& _extinction,
		float & fresnel_scale,
		Vector3D& transmission)
{
	Vector3D normal = uvw.w();
	float cosine = dotProduct(in_dir, normal);

	if(cosine < 0.0f)
	{
		float temp1 = 1.0f /nt;
		cosine = -cosine;
		float root = 1.0f - (temp1*temp1) *(1.0f - cosine*cosine);
		transmission = in_dir *temp1 + normal * (temp1 *cosine -sqrt(root));
		_extinction = ColorRGB(1.0f, 1.0f, 1.0f);
	}
	else
	{
		float temp2 = dotProduct(in_dir, normal);
		float root = 1.0f - (nt*nt)*(1.0f - temp2 *temp2);
		if (root < 0.0f) return false;//total internal reflection
		else transmission = in_dir * nt + -normal * (nt*temp2 - sqrt(root));
		_extinction = extinction;
	}

	float temp3 = 1.0f - cosine;
	fresnel_scale = 1.0 - (R0 + (1.0f -R0) * temp3*temp3*temp3*temp3*temp3);
	return true;
}