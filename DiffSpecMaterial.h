#ifndef DIFF_SPEC_MATERIAL
#define DIFF_SPEC_MATERIAL

#include "Material.h"
#include "RNG.h"
#include "Shape.h"

class DiffSpecMaterial : public Material
{
public:
	DiffSpecMaterial() {}
	DiffSpecMaterial(Material* d, Material* s, float r0=.05f)
	{ diff_mat = d; spec_mat = s; R0 = r0;}

	virtual ColorRGB ambientResponse(const ONB&,
		const Vector3D&,
		const Vector3D&,
		const Vector2D&);

	virtual bool explicitBrdf(const ONB&,
		const Vector3D&,
		const Vector3D&,
		const Vector3D&,
		const Vector2D&,
		ColorRGB&);

	virtual bool scatterDirection(const Vector3D&,	//incident vector
		const HitRecord&,							// hit we are shading
		Vector2D&,									//random seed
		ColorRGB&,									//color to attentuate by
		bool&,										//count emitted light
		float&,										//brdf scale
		Vector3D&);									//scattered direction

	float R0;
	RNG rng;
	Material* diff_mat;
	Material* spec_mat;

};
#endif