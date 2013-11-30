#include "Vector3D.h"

void Vector3D::printOut () const {
	if(getX() < 0.0 || getX() > 0.0) {
		printf("x: %f", getX());
		printf(" y: %f", getY());
		printf(" z: %f\n", getZ());
	}
}

float tripleProduct(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3) {
	return dotProduct((cross(v1, v2)), v3);
}

Vector3D::~Vector3D ()
{
}