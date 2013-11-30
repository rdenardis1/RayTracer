#ifndef MESH_H
#define MESH_H
#include "Vertex.h"
#include "Shape.h"
#include "Texture.h"


class Mesh
{
public:
	Mesh();
	~Mesh();
	Texture * getTexture() const {return tex;}

	Texture* tex;
	Vector3D* vertices;
	VertexUV* vertUVs;
	VertexN* vertNs;
	VertexUVN* vertUVNs;

};


#endif