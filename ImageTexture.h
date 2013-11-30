#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "Texture.h"

class Image;

class ImageTexture : public Texture
{
public:
	ImageTexture(char* file_name);
	virtual ColorRGB value(const Vector2D& uv, const Vector3D& p) const;

	Image* image;

};
#endif