#include "NoiseTexture.h"

ColorRGB NoiseTexture::value(const Vector2D& uv, const Vector3D& p) const
{
	float t = (1.0f + solid_noise.noise(p*scale)) / 2.0f;
	return t*c0 + (1.0f -t)*c1;
}