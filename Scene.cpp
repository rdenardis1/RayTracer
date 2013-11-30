# include "Scene.h"

Scene::Scene(std::vector<Sphere> s, ColorRGB bColor)
{
	spheres= s;
	backgroundColor = bColor;
}

Scene::Scene()
{
	//possibly should initialize an empty vector of spheres
	backgroundColor = ColorRGB(0, 0,0);
}

ColorRGB Scene::getBackgroundColor() const {
	return backgroundColor;
}

ColorRGB Scene::trace(Ray3D ray, float min, float max) const {
	//TODO: implement this!
	return ColorRGB(0,0,0);
}



Scene::~Scene()
{
}