# include "PointLightSource.h"

PointLightSource::PointLightSource (Vector3D p, ColorRGB c)
{
	position = p;
	color = c;
}

PointLightSource::PointLightSource()
{
	position = Vector3D(0, 0, 0);
	color = ColorRGB(0, 0,0);
}

Vector3D PointLightSource::getPosition() const {
	return position;
}


ColorRGB PointLightSource::getColor() const {
	return color;
}

void PointLightSource::printOut () const {
	printf("position ");
	position.printOut();

}

PointLightSource::~PointLightSource ()
{
}