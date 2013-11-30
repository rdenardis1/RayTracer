// Adapted from Realistic Ray Tracing
//Sample.h
#ifndef SAMPLE_H
#define SAMPLE_H

#include<math.h>

class Vector2D;

//2D sampling
void random(Vector2D* samples, int num_samples);
//num samples must be a perfect square
void jitter(Vector2D* samples, int num_samples);
void nrooks(Vector2D* samples, int num_samples);
void multiJitter(Vector2D* samples, int num_samples);
void shuffle(Vector2D* samples, int num_samples);

void boxFilter(Vector2D* samples, int num_samples);
void tentFilter(Vector2D* samples, int num_samples);
void cubicSplineFilter(Vector2D* samples, int num_samples);

void random(float* samples, int num_samples);
void jitter(float* samples, int num_samples);
void shuffle(float* samples, int num_samples);


//helps to solve for cubicSplineFilter
inline float solve(float r) {
	float u = r;
	for (int i=0; i < 5; i++) 
		u = (11.0f * r + u * u *(6.0f + u*(8.0f - 9.0f * u))) / (4.0f + 12.0f * u * (1.0f + u * (1.0f - u)));
	return u;
}

inline float cubicFilter(float x) {
	if (x < 1.0f / 24.0f) 
		return pow(24*x, 0.25f) - 2.0f;
	else if (x < 0.5)
		return solve(24.0f * (x - 1.0f /24.0f) / 11.0f ) - 1.0f;
	else if (x < 23.0f/24.0f)
		return 1.0f - solve(24.0f * (23.0f /24.0f - x) /11.0f);
	else 
		return 2 - pow(24.0f * (1.0f -x), 0.25f);
}

#endif