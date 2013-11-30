// Adapted from Realistic Ray Tracing
#ifndef CAMERA_H
#define CAMERA_H

#include "Ray3D.h"
#include "ONB.h"

class Camera 
{
	public:
		Camera() {}
		Camera (const Camera& orig)
		{
			center = orig.center;
			corner = orig.corner;
			across = orig.across;
			up = orig.up;
			uvw = orig.uvw;
			u0 = orig.u0;
			u1 = orig.u1;
			v0 = orig.v0;
			v1 = orig.v1;
			d = orig.d;
			lens_radius = orig.lens_radius;
		}
		Camera(Vector3D c, Vector3D gaze, Vector3D vup, float aperture, float left, float right, float bottom, float top, float distance):
			center(c), d(distance), u0(left), u1(right), v0(bottom), v1(top){
			lens_radius = aperture/2.0F;
			printf("lens radius %f", lens_radius);
			uvw.initFromWV( -gaze, vup);
			corner = center + u0*uvw.u() + v0*uvw.v() - d*uvw.w();
			across  = (u1 -u0)*uvw.u();
			up = (v1-v0)*uvw.v();
		}		
		Ray3D getRay(float a, float b, float xi1, float xi2) 
		{
			/*
			Vector3D origin = center + uvw.u() + uvw.v();
			Vector3D target = corner + across*a+ + up*b;
			return Ray3D(center, unitVector(target-center));*/

			Vector3D origin = center + 2.0F*(xi1-0.5F)*lens_radius*uvw.u() + 2.0F*(xi2-0.5F)*lens_radius*uvw.v();
			Vector3D target = corner + across*a + up*b;
			return Ray3D(origin, unitVector(target-origin));
			//start off by computing from just u and v
			/*float uVal = u0 + (u1-u0)*a;
			float vVal = v1 + (v1-v0)*a;
			return Ray3D(center, unitVector(-d*unitVector(uvw.w()) + uVal*unitVector(uvw.u() )+ vVal*unitVector(uvw.v())));*/

		}

		Vector3D center, corner, across, up;
		ONB uvw;
		float lens_radius;
		float u0, u1, v0, v1;
		float d;
};

#endif //CAMERA_H