#ifndef MATRIX_H
#define MATRIX_H

#include "Vector3D.h"
#include "math.h"

class Matrix
{
public:
	Matrix() {}
	Matrix(const Matrix & orig);

	void invert();
	void transpose();
	Matrix getInverse() const;
	Matrix getTranspose() const;

	Matrix & operator+= (const Matrix& right_op);
	Matrix & operator-= (const Matrix& right_op);
	Matrix & operator*= (const Matrix& right_op);
	Matrix & operator*= (float right_op);

	friend Matrix operator- (const Matrix& left_op, const Matrix& right_op);
	friend Matrix operator+ (const Matrix& left_op, const Matrix& right_op);
	friend Matrix operator* (const Matrix& left_op, const Matrix& right_op);
	friend Vector3D operator* (const Matrix& left_op, const Vector3D& right_op);
	friend Matrix operator* (const Matrix & left_op,  float right_op);

	friend Vector3D transformLoc(const Matrix& left_op, const Vector3D& right_op);
	friend Vector3D transformVec(const Matrix& left_op, const Vector3D& right_op);

	friend Matrix zeroMatrix();
	friend Matrix identityMatrix();
	friend Matrix translate(float _x, float _y, float _z);
	friend Matrix scale(float _x, float _y, float _z);
	friend Matrix rotate(const Vector3D & axis, float angle);
	friend Matrix rotateX(float angle);
	friend Matrix rotateY(float angle);
	friend Matrix rotateZ(float angle);

	friend Matrix viewMatrix(const Vector3D& eye, const Vector3D & gaze, const Vector3D& up);
	
	float determinant();
	float x[4][4];
};

//3x3 matrix 

inline float det3 (float a, float b, float c,
				   float d, float e, float f,
				   float g, float h, float i)
{ return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f;}

#endif 