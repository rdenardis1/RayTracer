#include "DiffSpecMaterial.h"

ColorRGB DiffSpecMaterial::ambientResponse(const ONB& uvw, const Vector3D& v_in, const Vector3D& p, const Vector2D& uv)
{
	float cosine = dotProduct(v_in, uvw.w());
	if (cosine < 0.0f) cosine = -cosine;
	float temp1 = 1.0f - cosine;
	float R = R0 + (1.0f - R0) *temp1*temp1*temp1*temp1*temp1;
	float P = (R + 0.5f) / 2.0f;
	if(rng() <= P)
		return spec_mat->ambientResponse(uvw, v_in, p, uv);
	else
		return diff_mat->ambientResponse(uvw, v_in, p, uv);
}

bool DiffSpecMaterial::explicitBrdf(const ONB& uvw, const Vector3D& v0, const Vector3D& v1, const Vector3D& p, 
									const Vector2D& uv, ColorRGB& brdf)
{return diff_mat->explicitBrdf(uvw, v0, v1, p, uv, brdf);}

bool DiffSpecMaterial::scatterDirection(const Vector3D& v_in, const HitRecord & rec, Vector2D& seed, ColorRGB& color, bool& CEL,
										float& brdf, Vector3D& v_out)
{
	float cosine = dotProduct(v_in, rec.uvw.w());
	if (cosine <0.0f) cosine = -cosine;
	float temp1 = 1.0f - cosine;
	float R = R0 + (1.0f - R0) *temp1*temp1*temp1*temp1*temp1;
	float P = (R + 0.5f) / 2.0f;
	if(rng() <= P)
	{
		brdf = R/P;
		return spec_mat->scatterDirection(v_in, rec, seed, color, CEL, temp1, v_out);
	}
	else 
	{
		brdf = (1.0f - R)/ (1.0f- P);
		return diff_mat->scatterDirection(v_in, rec, seed, color, CEL, temp1, v_out);
	}
}
