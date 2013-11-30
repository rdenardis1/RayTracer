# include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera (Vector3D eyeVector, Vector3D uVector, Vector3D vVector, Vector3D wVector, 
			float left, float right, float top, float bottom, int xRes, int yRes) {
				eye = eyeVector;
				u = uVector;
				v = vVector;
				w = wVector;
				l = left;
				r = right;
				t = top;
				b = bottom;
				xResolution = xRes;
				yResolution = yRes;
}

OrthographicCamera::OrthographicCamera ()
{
	eye = Vector3D(0, 0, 0);
	u = Vector3D(0, 0, 0);
	v = Vector3D(0, 0, 0);
	w = Vector3D(0, 0, 0);
	l = 0.0;
	r = 0.0;
	t = 0.0;
	b = 0.0;
	xResolution = 0;
	yResolution = 0;
}


Ray3D OrthographicCamera::getViewRay(int i, int j)
{
	float uScalar = l + (r-l)* (i+0.5)/(xResolution*1.0);
	float vScalar = b + (t-b)*(j+0.5)/(yResolution*1.0);
	Vector3D viewDirection = Vector3D(0, 0, 0) - w;
	Vector3D origin = eye + u * uScalar + v * vScalar;
	return Ray3D(origin, viewDirection);

}

void OrthographicCamera::printOut () const {
	printf("u vector ");
	u.printOut();
	printf("v vector ");
	v.printOut();
	printf("w vector ");
	w.printOut();
}

OrthographicCamera::~OrthographicCamera()
{
}