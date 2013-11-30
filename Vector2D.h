#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Vector2D
{
	
	
	private:
		float e[2];

	public:
		Vector2D(){}
		Vector2D(float xVal, float yVal);
		~Vector2D(){}		
		float getX() const { return e[0];}
		float getY() const { return e[1];}
		const Vector2D& operator+() const;
		Vector2D operator-() const;

		float operator[](int i) const { return e[i];}
		//float& operator[](int i) const { return e[i];}

		float length() const;
		float squaredLength() const;
		void makeUnitVector();

		void scramble();

		void setX(float x) {e[0] = x;}
		void setY(float y) {e[1] = y;}
		float minComponent() const;
		float maxComponent() const;
		float maxAbsComponent() const;
		float minAbsComponent() const;
		int indexOfMinComponent() const;
		int indexOfMaxComponent() const;
		int indexOfMinAbsComponent() const;
		int indexOfMaxAbsComponent() const;

		friend bool operator==(const Vector2D& v1, const Vector2D& v2);
		friend bool operator!=(const Vector2D& v1, const Vector2D& v2);
		
		friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D operator/(const Vector2D& vec, float scalar);
		friend Vector2D operator*(const Vector2D& vec, float scalar);
		friend Vector2D operator*(float scalr, const Vector2D& vec);

		Vector2D& operator=(const Vector2D& v2);
		Vector2D& operator+=(const Vector2D& v2);
		Vector2D& operator-=(const Vector2D& v2);
		Vector2D& operator*=(const float scalar);
		Vector2D& operator/=(const float scalar);

		friend Vector2D unitVector(const Vector2D& v);
		friend Vector2D minVec(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D maxVec(const Vector2D& v1, const Vector2D& v2);
		friend Vector2D cross(const Vector2D& v1, const Vector2D& v2);
		friend float dotProduct(const Vector2D& v1, const Vector2D& v2);
		//friend float tripleProduct(const Vector2D& v1, const Vector2D& v2, const Vector2D& v2);

};

inline Vector2D::Vector2D(float x, float y)
{ 
	e[0] = x;
	e[1] = y;
}

inline const Vector2D& Vector2D::operator+() const {
	return *this;
}

inline Vector2D Vector2D::operator-() const {
	return Vector2D(-e[0], -e[1]);
}
inline float Vector2D::length() const {
	return sqrt(e[0]*e[0]+ e[1]*e[1]);
}
inline float Vector2D::squaredLength() const {
	return e[0]*e[0]+ e[1]*e[1];
}
inline void Vector2D::makeUnitVector() 
{ *this = *this / (*this).length();}

inline float Vector2D::minComponent() const {
	float temp = e[0];
	if (e[1] < temp) temp = e[1];
	return temp;
}

inline float Vector2D::maxComponent() const {
	float temp = e[0];
	if (e[1] > temp) temp = e[1];
	return temp;
}

inline float Vector2D::maxAbsComponent() const {
	float temp = fabs(e[0]);
	if (fabs(e[1]) > temp) temp = fabs(e[1]);
	return temp;
}

inline float Vector2D::minAbsComponent() const {
	float temp = fabs(e[0]);
	if (fabs(e[1]) < temp) temp = fabs(e[1]);
	return temp;
}

inline int Vector2D::indexOfMinComponent() const {
	int index = 0;
	float temp = e[0];
	if (e[1] < temp) 
	{
		index= 1;
	}
	return index;
}

inline int Vector2D::indexOfMaxComponent() const {
	int index = 0;
	float temp = e[0];
	if (e[1] > temp) 
	{
		index= 1;
	}
	return index;
}

inline int Vector2D::indexOfMaxAbsComponent() const {
	int index = 0;
	float temp = fabs(e[0]);
	if (fabs(e[1]) > temp) 
	{
		index = 1;
	}
	return index;
}

inline int Vector2D::indexOfMinAbsComponent() const {
	int index = 0;
	float temp = fabs(e[0]);
	if (fabs(e[1]) < temp) 
	{
		index= 1;
	}
	return index;
}

inline bool operator==(const Vector2D& v1, const Vector2D& v2) {
	if (v1.e[0] != v2.e[0]) return false;
	if (v1.e[1] != v2.e[1]) return false;
	return true;
}

inline bool operator!=(const Vector2D& v1, const Vector2D& v2) {
	return !(v1==v2);
}

inline Vector2D operator*(float scalar, const Vector2D& vec) {
	return Vector2D(vec.e[0]*scalar, vec.e[1]*scalar);
}

inline Vector2D operator*( const Vector2D& vec, float scalar) {
	return Vector2D(vec.e[0]*scalar, vec.e[1]*scalar);
}

inline Vector2D operator/( const Vector2D& vec, float scalar) {
	return Vector2D(vec.e[0]/scalar, vec.e[1]/scalar);
}

inline Vector2D operator+( const Vector2D& v1, const Vector2D& v2) {
	return Vector2D(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1]);
}

inline Vector2D operator-( const Vector2D& v1, const Vector2D& v2) {
	return Vector2D(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1]);
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v2) {
	*this = *this - v2;
	return *this;
}

inline Vector2D& Vector2D::operator=(const Vector2D& v2) {
	e[0] = v2.e[0];
	e[1] = v2.e[1];
	return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v2) {
	*this = *this - v2;
	return *this;
}

inline Vector2D& Vector2D::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}
inline Vector2D& Vector2D::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}
inline float dotProduct(const Vector2D &v1, const Vector2D &v2) {
	return v1.getX()*v2.getX() + v1.getY()*v2.getY();
}


inline Vector2D unitVector(const Vector2D& vec) {
	float length = vec.length();
	return vec/ length;
}

inline Vector2D minVec(const Vector2D& v1, const Vector2D& v2) {
	Vector2D vec(v1);
	if( v2.getX() < v2.getX()) vec.setX(v2.getX());
	if( v1.getY() < v2.getY()) vec.setY(v2.getY());
	return vec;
}

inline Vector2D maxVec(const Vector2D& v1, const Vector2D& v2) {
	Vector2D vec(v1);
	if( v2.getX() > v2.getX()) vec.setX(v2.getX());
	if( v1.getY() > v2.getY()) vec.setY(v2.getY());
	return vec;
}

inline void Vector2D::scramble() {
	setX(((double) rand() / (RAND_MAX)));
	setY(((double) rand() / (RAND_MAX)));
}

#endif //VECTOR2D_H