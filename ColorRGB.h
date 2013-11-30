/* Closely follows code in Realistic Ray Tracing.
 * 
 */
#ifndef COLORRGB_H
#define COLORRGB_H
// Adapted from Realistic Ray Tracing
#include <iostream>

class ColorRGB
{
	
	private:
		float red;
		float green;
		float blue;

	public:
		ColorRGB() { red = green = blue = 0;}
		ColorRGB(float r, float g, float b);
		ColorRGB(const ColorRGB & original) { *this = original;}

		void setRed(float r) { red = r;}
		void setGreen(float g) { green = g;}
		void setBlue(float b) { blue = b;}

		float getRed() const { return red;}
		float getGreen() const {return green;}
		float getBlue() const {return blue;}

		ColorRGB& operator=(const ColorRGB & right_op);
		ColorRGB& operator+=(const ColorRGB & right_op);
		ColorRGB& operator*=(const ColorRGB & right_op);
		ColorRGB& operator/=(const ColorRGB & right_op);
		ColorRGB& operator*=(float right_op);
		ColorRGB& operator/=(float right_op);

		ColorRGB operator+()const { return *this;}
		ColorRGB operator-()const { return ColorRGB(-red, -green, -blue);}

		void clamp();

		
		friend std::ostream& operator<<(std::ostream & out, const ColorRGB & rgb);
		/* These "friend" methods allow us to use the +,-,/ without calling on a specific color value.*/
		friend ColorRGB operator*(const ColorRGB& c, float f);
		friend ColorRGB operator*(float f, const ColorRGB& c);
		friend ColorRGB operator/(const ColorRGB& c, float f);
		friend ColorRGB operator*(const ColorRGB& c1, const ColorRGB& c2);
		friend ColorRGB operator/(const ColorRGB& c1, const ColorRGB& c2);
		friend ColorRGB operator+(const ColorRGB& c1, const ColorRGB& c2);

		void printOut() const;
};

inline ColorRGB::ColorRGB(float r, float g, float b): red(r), green(g), blue(b) {}

inline ColorRGB& ColorRGB::operator+=(const ColorRGB & right_op) {
	*this = *this + right_op;
	return *this;
}

inline ColorRGB& ColorRGB::operator*=(float right_op) {
	*this = *this * right_op;
	return *this;
}

inline ColorRGB& ColorRGB::operator/=(float right_op) {
	*this = *this / right_op;
	return *this;
}

inline ColorRGB& ColorRGB::operator*=(const ColorRGB & right_op) {
	*this = *this * right_op;
	return *this;
}

inline ColorRGB& ColorRGB::operator/=(const ColorRGB & right_op) {
	*this = *this /right_op;
	return *this;
}

inline ColorRGB& ColorRGB::operator=(const ColorRGB & right_op) {
	red = right_op.getRed();
	green = right_op.getGreen();
	blue = right_op.getBlue();
	return *this;
}

inline void ColorRGB::clamp() {
	if (red > 1.0f) red = 1.0f;
	if (green > 1.0f) green = 1.0f;
	if (blue > 1.0f) blue = 1.0f;
	if (red < 0.0f) red = 0.0f;
	if (green < 0.0f) green = 0.0f;
	if (blue < 0.0f) blue = 0.0f;
}


inline ColorRGB operator*(const ColorRGB& c, float f) {
	return ColorRGB(c.getRed()*f , c.getGreen()*f, c.getBlue()*f);
}

inline ColorRGB operator*(float f, const ColorRGB& c ) {
	return ColorRGB(c.getRed()*f , c.getGreen()*f, c.getBlue()*f);
}

inline ColorRGB operator/(const ColorRGB& c, float f) {
	return ColorRGB(c.getRed()/f, c.getGreen()/f, c.getBlue()/f);
}

inline ColorRGB operator*(const ColorRGB& c1, const ColorRGB& c2) {
	return ColorRGB(c1.getRed()*c2.getRed(), c1.getGreen()*c2.getGreen(), c1.getBlue()*c2.getBlue());
}

inline ColorRGB operator/(const ColorRGB& c1, const ColorRGB& c2) {
	return ColorRGB(c1.getRed()/c2.getRed(), c1.getGreen()/c2.getGreen(), c1.getBlue()/c2.getBlue());
}
inline ColorRGB operator+(const ColorRGB& c1, const ColorRGB& c2) {
	return ColorRGB(c1.getRed()+c2.getRed(), c1.getGreen()+c2.getGreen(), c1.getBlue()+c2.getBlue());
}

inline void ColorRGB::printOut() const{
	printf("red: %f\n", red);
	printf("green: %f\n", green);
	printf("blue: %f\n", blue);
}

#endif
