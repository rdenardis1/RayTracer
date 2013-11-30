
#define _CRT_SECURE_NO_DEPRECATE 
 
#include <iostream>
#include <math.h>
#include <vector>
#include "Vector3D.h"
#include "Point3D.h"
#include "sphere.h"
#include "Ray3D.h"
#include "OrthographicCamera.h"
#include "PointLightSource.h"
#include "Image.h"
#include "Camera.h"
#include "Triangle.h"
#include "Vector2D.h"
#include "Sample.h"
#include "SimpleTexture.h"
#include "MarbleTexture.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "UVSphere.h"
#include "TestMaterial.h"
#include "DiffuseMaterial.h"
#include "PhongMetalMaterial.h"
#include "Parallelogram.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif


 int width = 500;
 int height = 500;
 std::vector<Shape*> shapes;
float max = 255;
int maxDepth = 5;
 
Image* image;
 
ColorRGB getRadiance(Ray3D r, int depth) 
{
	float tmax = 100000.0f;
	bool hit = false;
	HitRecord rec;
	for (int k=0; k<shapes.size(); k++) {
		if(shapes[k]->hit(r, .00001f, tmax,0, rec))
		{
			tmax = rec.t;
			hit = true;
		}
	}
	if (hit) 
	{
		Material* mat = rec.mat_ptr;
		ColorRGB ret =  mat->ambientResponse(rec.uvw, rec.texp, rec.p, rec.uv);
		if (mat->emits()) {
			ret += mat->emittedRadiance(rec.uvw, rec.p, rec.texp, rec.uv);	
		}
		if (mat->isDiffuse())
		{	
			Vector2D seed(0.5, 0.5);
			ColorRGB diffuseColor;
			Vector3D v_out;
			mat->diffuseDirection(rec.uvw, rec.texp, rec.p, rec.uv, seed, diffuseColor, v_out);
			Ray3D nextRay = Ray3D(rec.p, v_out);
			if(depth < maxDepth) {
				ret += diffuseColor*getRadiance(nextRay,depth+1);
			}
		}

		if (mat->isSpecular())
		{
			Vector2D seedSpec(0.5, 0.5);
			ColorRGB specularColor;
			Vector3D v_outSpec;
			Vector3D v_in = r.getDirection();
			v_in.makeUnitVector();
			mat->specularDirection(rec.uvw,v_in , rec.p, rec.uv, seedSpec, specularColor, v_outSpec);
			Ray3D nextRay = Ray3D(rec.p, v_outSpec);
			if(depth < maxDepth) {
				ret += specularColor*getRadiance(nextRay,depth+1);
			}
		}
		return ret;		
	}
	else 
	{
		//background color 
		return ColorRGB(0, 0, 0);
		//return ColorRGB(.2,.2, .2);			
	}
}

void rayTraceWithSampling() {
	HitRecord rec;
	bool hit;
	float tmax;
	//direction of viewing rays
	Vector3D dir(0,0,-1);
	
	//add sphere to the shapes
	//shapes.push_back(new UVSphere(Vector3D(0,0,0), 1.5, &DiffuseMaterial(&ImageTexture("C:/Users/Becky/Documents/Visual\ Studio\ 2012/compsci342/RayTracer/RayTracer/checkerboard.ppm"))));
	//shapes.push_back(new Sphere(Vector3D(0,0,0), 1.5, &DiffuseMaterial(&SimpleTexture(ColorRGB(0.0, 0.2, 0.0)))));
	shapes.push_back(new Sphere(Vector3D(0,0,0), 1.5, &PhongMetalMaterial(&SimpleTexture(ColorRGB(.3,.3,.3)), &SimpleTexture( ColorRGB(.2, .2,.2)))));

	shapes.push_back(new Sphere(Vector3D(3.0, 0, 1.0), 0.5, &TestMaterial(&SimpleTexture(ColorRGB(0.0, 0.2, 0.0)))));
	shapes.push_back(new Sphere(Vector3D(3.0, 0, -1.0), 0.5, &PhongMetalMaterial(&SimpleTexture(ColorRGB(.2,.2,.2)), &SimpleTexture( ColorRGB(.2, .2,.2)))));
	shapes.push_back(new Parallelogram(Vector3D(- 4, -4, -4), Vector3D(0, 8, 0), Vector3D(0, 0, 8), &DiffuseMaterial(&SimpleTexture(ColorRGB(.5, 0, 0))))); 

	//add triangle to the shpes
	//shapes.push_back(new Triangle(Vector3D(0,0, 1.5),Vector3D(0, 0.4, 1.5), Vector3D(.2, 0, 1.5), &SimpleTexture(ColorRGB(.1, 0.8, 0.2))));
	// intialize the camera (center, gaze, vup, aperture, left, right, bottom, top, distance)
	Camera camera = Camera(Vector3D(12,0,0), Vector3D (-1,0,0), Vector3D (0,1,0), 0.0, -1.0, 1.0, -1.0, 1.0, 3.0);
	for (int i=0; i < 500; i++)
		for(int j=0; j< 500;j++) {
			//pick multiple samples for each pixel
			Vector2D* samples = new Vector2D[16];
			jitter(samples, 4);
			boxFilter(samples, 4);
			ColorRGB colorSum = ColorRGB(0,0,0);
			for(int sampleIndex = 0; sampleIndex < 4; sampleIndex++) 
			{
				Vector2D vecInViewPlane = samples[sampleIndex];
				
				//this should be done differently (just getting the points at random would be better)
				Vector2D* lensSample = new Vector2D;
				jitter(lensSample, 1);
				boxFilter(lensSample, 1);
				//Check to make sure that this is correct (is the +0.5 necessary?)
				Ray3D r = camera.getRay((vecInViewPlane.getX()+i+0.5)/500,(vecInViewPlane.getY()+j+0.5)/500, lensSample[0].getX(), lensSample[0].getY());
				colorSum += getRadiance(r, 0);

			}
			image->set(i, j, colorSum/4.0);
	}
	image->writeImage("C:/Users/Becky/Documents/CompSci344/test.ppm");     
}



void init( void ){
    glClearColor(0.0, 0.0, 0.0, 0.0);
	rayTraceWithSampling();
}
 
void idle( void ){
     
    glutPostRedisplay();
}
 
void drawImage( void ){
 
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2i(0, 0);
        glDrawPixels(500, 500, GL_RGB, GL_FLOAT,
			image->getImageDisplayArray());
		
}
 
void display( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    drawImage();
     
    glFlush();
}
 
void reshape( int w, int h )
{
    width = w;
    height = h;
    glViewport( 0, 0, width, height );
    glutPostRedisplay();
}
 
void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
    }
}

 
int main(int argc, char * argv[])
{
    glutInit( &argc, argv );
     
    glutInitDisplayMode( GLUT_RGB );
    glutInitWindowSize( 500, 500);
     
    glutCreateWindow( "Image" );
	image = new Image(500, 500);
     
    init();
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
  
    glutMainLoop();    
    return 0;
}
