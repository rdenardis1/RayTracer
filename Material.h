
#ifndef MATERIAL_H
#define MATERIAL_H
#include "Vector2D.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "ColorRGB.h"
#include "ONB.h"
#include "Shape.h"

#define PI 3.14159265359

class Material
{
public:
	virtual bool emits() const {return false;}
	virtual ColorRGB emittedRadiance(const ONB&, //ONB of hit point
		const Vector3D&, //outgoing directikon from light
		const Vector3D&, //texture point
		const Vector2D&)
	{ return ColorRGB(0,0,0);}

	virtual ColorRGB ambientResponse(const ONB&, //ONB of hit point
		const Vector3D&, //incident direction
		const Vector3D&, //texture point
		const Vector2D&) //texture coordinate
	{ return ColorRGB(0,0,0);}

	virtual bool explicitBrdf(const ONB&, //ONB of hit point
		const Vector3D&,		//outoging vector v0
		const Vector3D&,		//outgoing vector v1
		const Vector3D&,			//texture point
		const Vector2D&,		//texture coordinate
		ColorRGB&)
	{return false;}

	virtual bool diffuseDirection(const ONB&,	//ONB of hit point
		const Vector3D&,		//incident vector
		const Vector3D&,		//texture point
		const Vector2D&,		//texture coordinate
		Vector2D&,			//random seed
		ColorRGB&,			//value returned by texture
		Vector3D&) {return false;}

	virtual bool specularDirection(const ONB&,	//ONB of hit point
		const Vector3D&,		//incident vector
		const Vector3D&,		//texture point
		const Vector2D&,		//texture coordinate
		Vector2D&,			//random seed
		ColorRGB&,			//value returned by texture
		Vector3D&) {return false;}

	virtual bool transmissionDirection(const ONB&,
		const Vector3D&,		//incident vector
		const Vector3D&,		//texture point
		const Vector2D&,		//texture coordinate
		const Vector2D&,			//random seed
		ColorRGB&,			//extinction color
		float&,				//fresnel_scale
		Vector3D&) {return false;}


	virtual bool scatterDirection(const Vector3D&,	//incident vector
		const HitRecord&,							// hit we are shading
		Vector2D&,									//random seed
		ColorRGB&,									//color to attentuate by
		bool&,										//count emitted light
		float&,										//brdf scale
		Vector3D&){return false;}									//scattered direction

	virtual bool isDiffuse() {return false;}
	virtual bool isSpecular() {return false;}
	virtual bool isTransmissive() {return false;}
	virtual int causticPhotons() { return 0;}
	virtual int globalPhotons() { return 0;}
	virtual ColorRGB photonColor() { return ColorRGB(0.0f, 0.0f, 0.0f);}
};

#endif