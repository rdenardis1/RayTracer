// Adapted from Realistic Ray Tracing
#ifndef ONB_H
#define ONB_H

#include "Vector3D.h"
class ONB
{
	public:
		ONB() {};
		ONB(const Vector3D& a, const Vector3D& b, const Vector3D& c){ U =a; V = b; W = c;}
		void initFromU(const Vector3D& u);
		void initFromV(const Vector3D& v);
		void initFromW(const Vector3D& w);

		void set(const Vector3D& a, const Vector3D& b, const Vector3D& c) { U =a, V = b; W = c;}
		
		// Calculating the basis from two vectors. First vector is fixed, second's direction can be adjusted
		void initFromUV(const Vector3D& u, const Vector3D& v);
		void initFromVU(const Vector3D& v, const Vector3D& u);

		void initFromUW(const Vector3D& u, const Vector3D& w);
		void initFromWU(const Vector3D& w, const Vector3D& u);

		void initFromVW(const Vector3D& v, const Vector3D& w);
		void initFromWV(const Vector3D& w, const Vector3D& v);

		friend bool operator==(const ONB& o1, const ONB& o2);
		Vector3D u() const { return U;}
		Vector3D v() const { return V;}
		Vector3D w() const { return W;}


		Vector3D U, V, W;
};
#endif //ONB_H