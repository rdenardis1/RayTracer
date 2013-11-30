#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "Texture.h"
#include "ColorRGB.h"
#include "SolidNoise.h"

class NoiseTexture : public Texture {
public:
	NoiseTexture(float _scale = 0.1f) {
		scale = _scale;
		c0 = ColorRGB(0.0, 0.0, 0.4);
		c1 = ColorRGB(0.4, 0.0, 0.0);
	}

	NoiseTexture( const ColorRGB & _c0, const ColorRGB & _c1, float _scale)
		: c0(_c0), c1(_c1), scale(_scale) {}

	virtual ColorRGB value(const Vector2D& uv, const Vector3D& p) const;

	float scale;
	ColorRGB c0, c1;
	SolidNoise solid_noise;
};


#endif