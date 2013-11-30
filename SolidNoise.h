#ifndef SOLID_NOISE_H
#define SOLID_NOISE_H

#include <math.h>
#include "Vector3D.h"

class SolidNoise {
public:
	SolidNoise();
	float noise(const Vector3D& p) const;
	float turbulence(const Vector3D& p, int depth) const;
	float dturbulence(const Vector3D& p, int depth, float d) const;
	float omega(float t) const;
	Vector3D gamma(int i, int j, int k) const;
	int intGamma(int i, int j) const;
	float knot(int i, int j, int k, Vector3D& v) const;

	Vector3D grad[16];
	int phi[16];
};

inline float SolidNoise::omega(float t) const {
	t = (t > 0.0f)? t : -t;
	return (-6.0f*t*t*t*t*t + 15.0f*t*t*t*t -10.0f*t*t*t +1.0f);
}

inline Vector3D SolidNoise::gamma(int i, int j, int k) const
{
	int idx;
	idx = phi[abs(k)%16];
	idx = phi[abs(j+idx) % 16];
	idx = phi[abs(i+idx) % 16];
	return grad[idx];
}

inline float SolidNoise::knot(int i, int j, int k, Vector3D& v)
	const {return (omega(v.getX()) * omega(v.getY()) * omega(v.getZ())) * (dotProduct(gamma(i,j,k), v));}

inline int SolidNoise::intGamma(int i, int j) const {
	int idx;
	idx = phi[abs(j)%16];
	idx = phi[abs(i+idx) % 16];
	return idx;
}
#endif //SOLID_NOISE_H