#include "MarbleTexture.h"

ColorRGB MarbleTexture::value(const Vector2D& uv, const Vector3D& p) const
{
	float temp = scale*noise.turbulence(freq*p, octaves);

	float t = 2.0f*fabs(sin(freq*p.getX() + temp));
	/*if (p.getX()!=0.0) {
		printf("temp: %f", p.getX());
	}
	if (sin(freq*p.getX() + temp) != 0.0) {
			printf("t %f",sin(freq*p.getX() + temp));
	}*/

	if (t < 1.0f) {
		return (c1*t + (1.0f - t)*c2);
	}
	else
	{

		t -= 1.0f;
		return (c0*t + (1.0f -t)*c1);
	}
}