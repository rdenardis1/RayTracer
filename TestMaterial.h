#ifndef TEST_MATERIAL_H
#define TEST_MATERIAL_H
#include "Material.h"
class Texture;

class TestMaterial : public Material
{
public:
	TestMaterial(Texture * t)
	{ R =t;}
	virtual ColorRGB ambientResponse(const ONB&,
		const Vector3D&,	//incident direction
		const Vector3D&,	//texture point
		const Vector2D& ); //texture coordinate

	virtual bool diffuseDirection(const ONB&,
		const Vector3D&,	//incident unit vector
		const Vector3D&,	//texture point
		const Vector2D&,	//texture coordinate
		Vector2D&,	//random seed
		ColorRGB&,
		Vector3D&);

	virtual ColorRGB emittedRadiance(const ONB&,
		const Vector3D&,
		const Vector3D&,
		const Vector2D&);

	virtual bool isDiffuse();
	bool emits() const  { return true;}

	Texture *R;
};



#endif