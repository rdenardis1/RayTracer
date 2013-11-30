#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"
#include "ColorRGB.h"
#include "Vector3D.h"

class Texture;

class DielectricMaterial : public Material
{

public:
	DielectricMaterial() {}
	DielectricMaterial(float nt, const ColorRGB& _ex);
	bool specularDirection(const ONB& uvw,
		const Vector3D& in_dir,		//incident vector
		const Vector3D& texp,		//texture point
		const Vector2D& uv,			//texture coordinate
		Vector2D& rseed,			// random seed
		ColorRGB& ratio,
		Vector3D& reflection);

	bool transmissionDirection(const ONB& uvw,
		const Vector3D& in_dir,		//incident unit vector
		const Vector3D& texp,		//texture point
		const Vector2D& uv,			//texture coordinate
		const Vector2D& rseed,		// random seed
		ColorRGB& _extinction,
		float & fresnel_scale,
		Vector3D& transmission);

	float R0;
	float nt;
	ColorRGB extinction;
};
#endif