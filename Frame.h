#ifndef FRAME_H
#define FRAME_H

#include "ONB.h"
#include "Vector3D.h"

class Frame {
	private:
		ONB basis;
		Vector3D origin;
	public:
		Frame() {basis = ONB(); origin = Vector3D();}
		Frame(const ONB& b, const Vector3D& o) {basis =b; origin = o;}
		ColorRGB() { red = green = blue = 0};
		ColorRGB(float r, float g, float b);
		ColorRGB(const ColorRGB & original) { *this = original;}
		void setBasis(const ONB & b) { basis = b;}
		void setOrigin(const Vector3D & o) {origin = o;}
		ONB getBasis() {return basis;}
		Vector3D getOrigin() { return origin;}

}


#endif //FRAME_H