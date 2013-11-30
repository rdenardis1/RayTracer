//Image.h
// Adapted from Realistic Ray Tracing and class

#ifndef IMAGE_H
#define IMAGE_H

#define _CRT_SECURE_NO_DEPRECATE 

#include <cmath>
#include <string>
#include <fstream>
#include "ColorRGB.h"
using namespace std;

class Image
{
	public:
		Image();
		Image(int width, int height);
		Image(int width, int height, ColorRGB background);
		Image(const char* file_name); 
		~Image(void);
		bool set(int x, int y, const ColorRGB & color);
		void gammaCorrect(float gamma);
		void writeImage(const char* file_name);
		float* getImageDisplayArray();
		int getWidth() {return nx;}
		int getHeight() {return ny;}
		ColorRGB getPixelValue(int x, int y) { return image[x][y];}
	
	private:
		ColorRGB ** image;
		char magic_number[2]; 
		int nx; //width
		int ny; //height
		int max;
		float* imageDisplayArray; 
};

#endif //IMAGE_H
