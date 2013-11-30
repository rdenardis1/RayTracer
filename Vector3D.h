// Adapted from Realistic Ray Tracing
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Vector3D
{
	private:
		float e[3];

	public:
		Vector3D(){e[0] = 0.0; e[1] = 0.0; e[2] = 0.0;}
		Vector3D(float xVal, float yVal, float zVal);
		~Vector3D ();		
		float getX() const { return e[0];}
		float getY() const { return e[1];}
		float getZ() const { return e[2];}
		const Vector3D& operator+() const;
		Vector3D operator-() const;

		float operator[](int i) const { return e[i];}
		//float& operator[](int i) const { return e[i];}

		float length() const;
		float squaredLength() const;
		void makeUnitVector();

		void setX(float x) {e[0] = x;}
		void setY(float y) {e[1] = y;}
		void setZ(float z) {e[2] = z;}
		float minComponent() const;
		float maxComponent() const;
		float maxAbsComponent() const;
		float minAbsComponent() const;
		int indexOfMinComponent() const;
		int indexOfMaxComponent() const;
		int indexOfMinAbsComponent() const;
		int indexOfMaxAbsComponent() const;

		friend bool operator==(const Vector3D& v1, const Vector3D& v2);
		friend bool operator!=(const Vector3D& v1, const Vector3D& v2);
		
		friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
		friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
		friend Vector3D operator/(const Vector3D& vec, float scalar);
		friend Vector3D operator*(const Vector3D& vec, float scalar);
		friend Vector3D operator*(float scalr, const Vector3D& vec);

		Vector3D& operator=(const Vector3D& v2);
		Vector3D& operator+=(const Vector3D& v2);
		Vector3D& operator-=(const Vector3D& v2);
		Vector3D& operator*=(const float scalar);
		Vector3D& operator/=(const float scalar);

		friend Vector3D unitVector(const Vector3D& v);
		friend Vector3D minVec(const Vector3D& v1, const Vector3D& v2);
		friend Vector3D maxVec(const Vector3D& v1, const Vector3D& v2);
		friend Vector3D cross(const Vector3D& v1, const Vector3D& v2);
		friend float dotProduct(const Vector3D& v1, const Vector3D& v2);
		friend float tripleProduct(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

		void printOut() const;
};

inline Vector3D::Vector3D(float x, float y, float z)
{ 
	e[0] = x;
	e[1] = y;
	e[2] = z;
}

inline const Vector3D& Vector3D::operator+() const {
	return *this;
}

inline Vector3D Vector3D::operator-() const {
	return Vector3D(-e[0], -e[1], -e[2]);
}
inline float Vector3D::length() const {
	return sqrt(e[0]*e[0]+ e[1]*e[1] + e[2]*e[2]);
}
inline float Vector3D::squaredLength() const {
	return e[0]*e[0]+ e[1]*e[1] + e[2]*e[2];
}
inline void Vector3D::makeUnitVector() 
{ *this = *this / (*this).length();}

inline float Vector3D::minComponent() const {
	float temp = e[0];
	if (e[1] < temp) temp = e[1];
	if (e[2] < temp) temp = e[2];
	return temp;
}

inline float Vector3D::maxComponent() const {
	float temp = e[0];
	if (e[1] > temp) temp = e[1];
	if (e[2] > temp) temp = e[2];
	return temp;
}

inline float Vector3D::maxAbsComponent() const {
	float temp = fabs(e[0]);
	if (fabs(e[1]) > temp) temp = fabs(e[1]);
	if (fabs(e[2]) > temp) temp = fabs(e[2]);
	return temp;
}

inline float Vector3D::minAbsComponent() const {
	float temp = fabs(e[0]);
	if (fabs(e[1]) < temp) temp = fabs(e[1]);
	if (fabs(e[2]) < temp) temp = fabs(e[2]);
	return temp;
}

inline int Vector3D::indexOfMinComponent() const {
	int index = 0;
	float temp = e[0];
	if (e[1] < temp) 
	{
		temp = e[1];
		index= 1;
	}
	if (e[2] < temp) index = 2;
	return index;
}

inline int Vector3D::indexOfMaxComponent() const {
	int index = 0;
	float temp = e[0];
	if (e[1] > temp) 
	{
		temp = e[1];
		index= 1;
	}
	if (e[2] > temp) index = 2;
	return index;
}

inline int Vector3D::indexOfMaxAbsComponent() const {
	int index = 0;
	float temp = fabs(e[0]);
	if (fabs(e[1]) > temp) 
	{
		temp = fabs(e[1]);
		index= 1;
	}
	if (fabs(e[2]) > temp) index = 2;
	return index;
}

inline int Vector3D::indexOfMinAbsComponent() const {
	int index = 0;
	float temp = fabs(e[0]);
	if (fabs(e[1]) < temp) 
	{
		temp = fabs(e[1]);
		index= 1;
	}
	if (fabs(e[2]) < temp) index = 2;
	return index;
}

inline bool operator==(const Vector3D& v1, const Vector3D& v2) {
	if (v1.e[0] != v2.e[0]) return false;
	if (v1.e[1] != v2.e[1]) return false;
	if (v1.e[2] != v2.e[2]) return false;
	return true;
}

inline bool operator!=(const Vector3D& v1, const Vector3D& v2) {
	return !(v1==v2);
}

inline Vector3D operator*(float scalar, const Vector3D& vec) {
	return Vector3D(vec.e[0]*scalar, vec.e[1]*scalar, vec.e[2]*scalar);
}

inline Vector3D operator*( const Vector3D& vec, float scalar) {
	return Vector3D(vec.e[0]*scalar, vec.e[1]*scalar, vec.e[2]*scalar);
}

inline Vector3D operator/( const Vector3D& vec, float scalar) {
	return Vector3D(vec.e[0]/scalar, vec.e[1]/scalar, vec.e[2]/scalar);
}

inline Vector3D operator+( const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1], v1.e[2]+v2.e[2]);
}

inline Vector3D operator-( const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1], v1.e[2]-v2.e[2]);
}

inline Vector3D& Vector3D::operator+=(const Vector3D& v2) {
	*this = *this - v2;
	return *this;
}

inline Vector3D& Vector3D::operator=(const Vector3D& v2) {
	e[0] = v2.e[0];
	e[1] = v2.e[1];
	e[2] = v2.e[2];
	return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& v2) {
	*this = *this - v2;
	return *this;
}

inline Vector3D& Vector3D::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}
inline Vector3D& Vector3D::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}
inline float dotProduct(const Vector3D &v1, const Vector3D &v2) {
	return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
}
inline Vector3D cross(const Vector3D & v1, const Vector3D & v2) {
	Vector3D temp;

	temp.e[0] = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
	temp.e[1] = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
	temp.e[2] = v1.getX() * v2.getY() - v1.getY() * v2.getX();
	return temp;
}

inline Vector3D unitVector(const Vector3D& vec) {
	float length = vec.length();
	return vec/ length;
}

inline Vector3D minVec(const Vector3D& v1, const Vector3D& v2) {
	Vector3D vec(v1);
	if( v2.getX() < v2.getX()) vec.setX(v2.getX());
	if( v1.getY() < v2.getY()) vec.setY(v2.getY());
	if( v1.getZ() < v2.getZ()) vec.setZ(v2.getZ());
	return vec;
}

inline Vector3D maxVec(const Vector3D& v1, const Vector3D& v2) {
	Vector3D vec(v1);
	if( v2.getX() > v2.getX()) vec.setX(v2.getX());
	if( v1.getY() > v2.getY()) vec.setY(v2.getY());
	if( v1.getZ() > v2.getZ()) vec.setZ(v2.getZ());
	return vec;
}

#endif //VECTOR3D_H