#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"
#include "Ray3D.h"

class OrthographicCamera
{
	
	private:
		//Should I construct the orthonormal basis for them, instead of presuming that it is one?
		Vector3D eye;
		Vector3D u;
		Vector3D v;
		Vector3D w;
		float l;
		float r;
		float t;
		float b;
		int xResolution;
		int yResolution;

	public:
		OrthographicCamera();
		OrthographicCamera (Vector3D eyeVector, Vector3D uVector, Vector3D vVector, Vector3D wVector, 
			float left, float right, float top, float bottom, int xRes, int yRes);
		~OrthographicCamera ();
		Ray3D getViewRay(int pixelI, int pixelJ);
		void printOut() const;
};

#endif
