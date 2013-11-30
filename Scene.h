#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#include "ColorRGB.h"

class Scene
{
	
	private:
		std::vector<Sphere> spheres;
		ColorRGB backgroundColor;

	public:
		Scene();
		Scene (std::vector<Sphere> s, ColorRGB bColor);
		~Scene ();
		ColorRGB trace(Ray3D ray, float min, float max) const;
		ColorRGB getBackgroundColor() const;
};

#endif
