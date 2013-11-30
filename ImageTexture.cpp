#include "ImageTexture.h"
#include "Image.h"

ImageTexture::ImageTexture(char* filename)
{
	image = new Image(filename);
}


ColorRGB ImageTexture::value(const Vector2D& uv, const Vector3D& p) const {
	float u = uv.getX() - int(uv.getX());
	float v = uv.getY() - int(uv.getY());
	u *= (image->getWidth() -3);
	v *= (image->getHeight() -3);
	int iu = (int) u;
	int iv = (int) v;

	float tu = u-iu;
	float tv = v-iv;

	ColorRGB c = image->getPixelValue(iu, iv)*(1-tu)*(1-tv) +
		image->getPixelValue(iu+1, iv)*tu*(1-tv)+
		image->getPixelValue(iu,iv +1)*(1-tu)*tv +
		image->getPixelValue(iu+1, iv+1)*tu*tv;
	return c;

}
