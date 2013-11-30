/** Adapted from Realistic Ray Tracing book and image processing assignment */
#include "Image.h"
#include <iostream>
using namespace std;

Image::Image()
{}

Image::Image(int width, int height)
{
	nx = width;
	ny = height;

	image = new ColorRGB*[nx];
	for (int i=0; i<nx; i++) {
		image[i] = new ColorRGB[ny];
	}
}

//Sets all pixels in the image to the backgroundColor
Image::Image(int width, int height, ColorRGB backgroundColor) {
	nx = width;
	ny = height;
	image = new ColorRGB*[nx];
	for (int i=0; i<nx; i++) {
		image[i] = new ColorRGB[ny];
		for (int j=0; j<ny; j++) {
			image[i][j] = backgroundColor;
		}
	}
}

Image::Image(const char* file_name){ 
       
    FILE* file; 
    char buff[16]; 
    float r, g, b; 
       
    file = fopen(file_name, "r"); // open file for reading 
       
    if(!file){ 
        fprintf(stderr, "Unable to open file %s", file_name); 
        exit(1); 
    } 
       
    fscanf(file, "%s%*[^\n]%*c", magic_number); //read magic number and white space 
       
    if(magic_number[0] != 'P' || magic_number[1] != '3'){ 
        printf("Incorrect file type"); 
        exit(1); 
    } 
       
    //check for comments 
    fscanf(file, "%s", buff); 
    while (strncmp(buff, "#", 1) == 0) { 
        fscanf(file, "%s%*[^\n]%*c", buff); 
    } 
       
    if (fscanf(file, "%d %d %d", &nx, &ny, &max) != 3) { 
        fprintf(stderr, "Invalid image size (error loading '%s')\n", file_name); 
        exit(1); 
    } 
       
    image = new ColorRGB*[nx];
    for(int i = 0; i < nx; i++) { 
		image[i] = new ColorRGB[ny];
		for (int j=0; j<ny; j++) {
            if(fscanf(file, "%f %f %f", &r, &g, &b) != 3){ 
                fprintf(stderr, "Invalid pixel reading\n"); 
                exit(1); 
            } 
            image[i][j] = ColorRGB(r/255.0, g/255.0, b/255.0);
		}
        
    } 
       
    fclose(file); 
    imageDisplayArray = NULL; 
} 

bool Image::set(int x, int y, const ColorRGB& color) {
	if (0 > x || x > nx) return false;
	if (0 > y || y > ny) return false;
	image[x][y] = color;
}

void Image::gammaCorrect(float gamma) {
	ColorRGB temp;
	float power = 1.0 / gamma;
	for (int i = 0; i < nx; i++) {
		for (int j=0; j < ny; j++) {
			temp = image[i][j];
			image[i][j] = ColorRGB(pow(temp.getRed(), power), pow(temp.getGreen(), power), pow(temp.getBlue(), power));
		}
	}
}

float* Image::getImageDisplayArray() { 
    if(imageDisplayArray != NULL) 
        return imageDisplayArray; 
    

    imageDisplayArray = new float[nx * ny * 3]; 
    int count = 0; 
    for(int i = ny -1; i >= 0; i--) { 
        for(int j = 0; j < nx; j++){
			imageDisplayArray[count] = image[j][i].getRed();
			count ++;
			imageDisplayArray[count] = image[j][i].getGreen();
			count++;
			imageDisplayArray[count] = image[j][i].getBlue();
			count++;  
        } 
    }      
    return imageDisplayArray; 
} 

void Image::writeImage(const char* file_name){ 
    FILE* file; 
    file = fopen(file_name, "w"); 
    if(!file){ 
        fprintf(stderr, "Unable to open file %s", file_name); 
        exit(1); 
    } 
  
    fprintf(file, "P3"); 
    fprintf(file, "\n"); 
    fprintf(file, "# CREATOR: GIMP PNM Filter Version 1.1\n"); 
    fprintf(file, "%d %d\n%d\n", nx, ny, 255);


  
    for(int i = 0; i < ny; i++) { 
        for(int j = 0; j<nx; j++){ 
            fprintf(file, "%d",((int) (image[j][i].getRed()*255))); 
			fprintf(file, " "); 
			fprintf(file, "%d",((int) (image[j][i].getGreen()*255))); 
			fprintf(file, " "); 
			fprintf(file, "%d",((int) (image[j][i].getBlue()*255))); 
			fprintf(file, " "); 
        } 
    } 
    fclose(file); 
       
} 


   
Image::~Image(void){ 
    for(int i = 0; i < nx; i++){ 
        delete [] image[i]; 
    } 
    delete [] image; 
       
    delete [] imageDisplayArray; 
} 