# include "Ray3D.h"

void Ray3D::printOut () const {
	printf("ray origin is: ");
	data[0].printOut();
	printf("ray direction is: ");
	data[1].printOut();
}

Ray3D::~Ray3D ()
{
}