#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector2D.h"
#include "Vector3D.h"
#include "ColorRGB.h"

class Texture 
{
public:
	virtual ColorRGB value(const Vector2D&, const Vector3D&) const = 0;
};

#endif //TEXTURE_H