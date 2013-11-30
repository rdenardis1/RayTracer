#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Point3D
{
	
	private:
		float x;
		float y;
		float z;

	public:
		Point3D();
		Point3D (float xVal, float yVal, float zVal);
		~Point3D ();
		float getX() const;
		float getY() const;
		float getZ() const;
		void printOut() const;
};

#endif
