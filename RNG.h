// From Realistic Ray Tracing
#ifndef RNG_H
#define RNG_H

class RNG 
{
	public:
		RNG(unsigned long long s = 7564231ULL)
		{
			seed = s;
			mult = 62089911ULL;
			llong_max = 4294967295ULL;
			float_max = 4294967295.0f;
		}
		float operator()();

		unsigned long long seed;
		unsigned long long mult;
		unsigned long long llong_max;
		float float_max;
};

inline float RNG::operator()()
{
	seed = mult * seed;
	return float(seed % llong_max) /float_max;
}
#endif