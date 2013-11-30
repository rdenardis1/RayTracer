#ifndef SIMPLE_TEXTURE_H
#define SIMPLE_TEXTURE_H

#include "Texture.h"

class SimpleTexture : public Texture
{
public:
	SimpleTexture(ColorRGB c) {color = c;}
	SimpleTexture() { color = ColorRGB(0.0, 0.0, 0.0);}
	virtual ColorRGB value(const Vector2D&, const Vector3D&) const
	{return color;}
	ColorRGB color;
};

#endif //SIMPLE_TEXTURE_H