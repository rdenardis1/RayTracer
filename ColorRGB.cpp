# include "ColorRGB.h"

ColorRGB::ColorRGB(float r, float g, float b)
{
	red = r;
	green = g;
	blue = b;
}


void ColorRGB::printOut () const {
	printf("red: %f", red);
	printf(" green: %f", green);
	printf(" blue: %f\n", blue);
}

ColorRGB::~ColorRGB()
{
}