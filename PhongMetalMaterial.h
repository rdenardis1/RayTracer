#ifndef PHONG_METAL_MATERIAL_H
#define PHONG_METAL_MATERIAL_H

#include "Material.h"

class Texture;

class PhongMetalMaterial : public Material {
public:
	PhongMetalMaterial(Texture *rt, Texture * et)
	{ R = rt; phong_exp = et;}

	virtual ColorRGB ambientResponse(const ONB&,
		const Vector3D&,
		const Vector3D&,
		const Vector2D&);

	virtual bool specularDirection(const ONB&,
		const Vector3D&,
		const Vector3D&,
		const Vector2D&,
		Vector2D&,
		ColorRGB&,
		Vector3D&);

	bool isSpecular() {return true;}

	Texture *R;
	Texture *phong_exp;

};

#endif