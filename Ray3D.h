#ifndef RAY3D_H
#define RAY3D_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"

class Ray3D
{
	
	public:
		Ray3D();
		Ray3D (const Vector3D & a, const Vector3D & b) {data[0] = a; data[1] =b;}
		Ray3D(const Ray3D& r) {*this = r;}
		~Ray3D ();
		Ray3D& operator=(const Ray3D& original) {setOrigin(original.data[0]); setDirection(original.data[1]); return *this;}
		Vector3D getOrigin() const {return data[0];}
		Vector3D getDirection() const {return data[1];}
		Vector3D getInvDirection() const { return data[2];}
		void setOrigin(const Vector3D & a) { data[0] = a;}
		void setDirection(const Vector3D & v) 
		{ 
			data[1] = v;
			data[2] = Vector3D(1.0f/ v.getX() , 1.0f/v.getY(), 1.0f/v.getZ());
			
			posneg[0] = (data[1].getX() > 0 ? 0 :1);
			posneg[1] = (data[1].getY() > 0 ? 0 :1);
			posneg[2] = (data[1].getZ() > 0 ? 0 :1);
			
		}
		Vector3D pointAtParameter(float t) const { return data[0] + t*data[1];}
		Vector3D data[3];		
		int posneg[3];
		void printOut() const;
};

#endif
