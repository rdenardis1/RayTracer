#ifndef MARBLE_TEXTURE
#define MARBLE_TEXTURE

#include <math.h>
#include "Texture.h"
#include "ColorRGB.h"
#include "SolidNoise.h"

#define PI 3.14159
class MarbleTexture : public Texture
{
public:
	MarbleTexture(float stripes_per_unit, float _scale = 5.0f, int _octaves = 8)
	{
		freq = PI  * stripes_per_unit;
		scale = _scale;
		octaves = _octaves;
		c0 = ColorRGB(0.8,0.8, 0.8);
		c1 = ColorRGB(0.4, 0.2, 0.1);
		c2 = ColorRGB(0.06, 0.04, 0.02);
	}

	MarbleTexture(const ColorRGB& _c0, const ColorRGB & _c1, const ColorRGB & _c2, float stripes_per_unit, float _scale = 3.0f,
			int _octaves = 8)
			: c0(_c0), c1(_c1), c2(_c2)
	{
		freq = PI* stripes_per_unit;
		scale = _scale;
		octaves = _octaves;
	}

	virtual ColorRGB value(const Vector2D& uv, const Vector3D& p) const;
	
	float freq, scale;
	int octaves;
	ColorRGB c0, c1, c2;
	SolidNoise noise;
};
#endif 