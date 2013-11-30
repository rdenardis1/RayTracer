# include "Point3D.h"

Point3D::Point3D (float xVal, float yVal, float zVal)
{
	x = xVal;
	y = yVal;
	z = zVal;
}

Point3D::Point3D()
{
	x = 0;
	y = 0;
	z = 0;
}


float Point3D::getX () const {
	return x;
}

float Point3D::getY () const {
	return y;
}

float Point3D::getZ () const {
	return z;
}

void Point3D::printOut () const {
	printf("x: %f", x);
	printf(" y: %f", y);
	printf(" z: %f\n", z);
}

Point3D::~Point3D ()
{
}