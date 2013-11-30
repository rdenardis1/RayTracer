#define _CRT_RAND_S

#include "Sample.h"
#include "Vector2D.h"
#include <math.h>
#include <stdlib.h>


void random(Vector2D* samples, int num_samples) 
	
{
	for (int i= 0; i< num_samples; i++) {
		samples[i].setX(((double) rand() / (RAND_MAX)));
		samples[i].setY(((double) rand() / (RAND_MAX)));
	}
}

void jitter(Vector2D* samples, int num_samples) 
{
	int sqrt_samples = (int) (sqrt(num_samples));
	for(int i=0; i <sqrt_samples; i++)
		for(int j=0; j<sqrt_samples; j++) 
		{
			float x = ((double) i + ((double) rand() / (RAND_MAX))) / (double) sqrt_samples;
			float y = ((double) j + ((double) rand() / (RAND_MAX))) / (double) sqrt_samples;
			(samples[i*sqrt_samples + j]).setX(x);
			(samples[i*sqrt_samples + j]).setY(y);
		}
}

void nrooks(Vector2D * samples, int num_samples )
{
	for( int i=0; i< num_samples; i++) 
	{
		samples[i].setX(((double) i + ((double) rand() / (RAND_MAX)) ) / (double) num_samples);
		samples[i].setY(((double) i + ((double) rand() / (RAND_MAX)) ) / (double) num_samples);
	}

	for (int i = num_samples - 2; i >= 0; i--)
	{
		int target = int(((double) rand() / (RAND_MAX)) *(double)i);
		float temp = samples[i+1].getX();
		samples[i+1].setX(samples[target].getX());
		samples[target].setX(temp);
	}
}

void multiJitter(Vector2D* samples, int num_samples) 
{
	int sqrt_samples = (int) sqrt(num_samples);
	float subcell_width = 1.0f/(float(num_samples));

	for (int i = 0; i <sqrt_samples; i++)
		for (int j=0; j<sqrt_samples; j++)
		{
			samples[i*sqrt_samples + j].setX(i*sqrt_samples*subcell_width + j*subcell_width + 
				((double) rand() / (RAND_MAX)) *subcell_width);
			samples[i*sqrt_samples + j].setY(j*sqrt_samples*subcell_width + i*subcell_width + 
				((double) rand() / (RAND_MAX)) *subcell_width);

		}
	// shuffle x coordinates withing each column and y coordinates within each row
		for (int i=0; i <sqrt_samples; i++) 
			for (int j=0; j<sqrt_samples; j++)
			{
				int k = j + int (((double) rand() / (RAND_MAX)) * (sqrt_samples - j -1));
				float t = samples[i*sqrt_samples + j].getX();
				samples[i*sqrt_samples + j].setX(samples[i*sqrt_samples + k].getX());
				samples[i* sqrt_samples + k].setX(t);
			}
}

void shuffle(Vector2D* samples, int num_samples) 
{
	for (int i=num_samples -2; i >= 0; i--)
	{
		int target = int(((double) rand() / (RAND_MAX)) * (double) i);
		Vector2D temp = samples[i+1];
		samples[i+1] = samples[target];
		samples[target] = temp;
	}
}

void boxFilter(Vector2D* samples, int num_samples) 
{
	for(int i=0; i < num_samples; i++) {
		samples[i].setX(samples[i].getX() - 0.5f);
		samples[i].setY(samples[i].getY() - 0.5f);
	}
}

void tentFilter(Vector2D* samples, int num_samples) 
{
	for (int i=0; i < num_samples; i++) 
	{
		float x = samples[i].getX();
		float y = samples[i].getY();
		if (x < 0.5f)
			samples[i].setX((float) sqrt(2.0*(double) x) -1.0f);
		else 
			samples[i].setX(1.0f - (float)sqrt(2.0 -2.0 * (double) x));
		if (y < 0.5f)
			samples[i].setY((float) sqrt(2.0*(double) y) -1.0f);
		else 
			samples[i].setY(1.0f - (float)sqrt(2.0 -2.0 * (double) y));

	}
}

void cubicSplineFilter(Vector2D * samples, int num_samples) 
{
	for (int i = 0; i < num_samples; i++)
	{
		float x = samples[i].getX();
		float y = samples[i].getY();

		samples[i].setX(cubicFilter(x));
		samples[i].setY(cubicFilter(y));
	}
}

void random(float * samples, int num_samples)
{
	for(int i = 0; i <num_samples; i++)
		samples[i] = ((double) rand() / (RAND_MAX));
}

void jitter(float * samples, int num_samples)
{
	for (int i = 0; i <num_samples; i++)
		samples[i] = ((double) i + ((double) rand() / (RAND_MAX))) / (double) num_samples;
}

void shuffle(float * samples, int num_samples)
{
	for (int i = num_samples -2; i >= 0; i--)
	{
		int target = int (((double) rand() / (RAND_MAX)) * (double) i);
		float temp = samples[i+1];
		samples[i+1] = samples[target];
		samples[target] = temp;
	}
}

