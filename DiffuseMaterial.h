#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H
#include "Material.h"
class Texture;

class DiffuseMaterial : public Material
{
public:
	DiffuseMaterial(Texture * t)
	{ R =t;}
	virtual ColorRGB ambientResponse(const ONB&,
		const Vector3D&,	//incident direction
		const Vector3D&,	//texture point
		const Vector2D& ); //texture coordinate

	virtual bool explicitBrdf(const ONB&,
		const Vector3D&,	//unit vector v1
		const Vector3D&,	//unit vector v0
		const Vector3D&,	//texture point
		const Vector2D&,	//texture coordinate
		ColorRGB&);

	virtual bool diffuseDirection(const ONB&,
		const Vector3D&,	//incident unit vector
		const Vector3D&,	//texture point
		const Vector2D&,	//texture coordinate
		Vector2D&,	//random seed
		ColorRGB&,
		Vector3D&);
	virtual bool isDiffuse();

	Texture *R;
};



#endif