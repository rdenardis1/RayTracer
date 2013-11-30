#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2D.h"
#include "Vector3D.h"

struct VertexUV
{
	Vector3D vertex;
	Vector2D uv;
};

struct VertexN
{
	Vector3D vertex;
	Vector3D normal;

};

struct VertexUVN
{
	Vector3D vertex;
	Vector2D uv;
	Vector3D normal;
};




#endif //VERTEX_H