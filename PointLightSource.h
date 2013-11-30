#ifndef POINTLIGHTSOURCE_H
#define POINTLIGHTSOURCE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"
#include "Ray3D.h"
#include "ColorRGB.h"

class PointLightSource
{
	
	private:
		Vector3D position;
		ColorRGB color;

	public:
		PointLightSource();
		PointLightSource (Vector3D p, ColorRGB c);
		~PointLightSource ();
		Vector3D getPosition() const;
		//have colors of lights represent intensities of light sources
		ColorRGB getColor() const;
		void printOut() const;
};

#endif
