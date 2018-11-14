#include "Color.h"

namespace VIX {
	Color::Color(const Color & color) : Color(color.r, color.g, color.b, color.a) {
	}
	Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a), combinedVal(r << 24 | g << 16 | b << 8 | a) {
	}
	Color::Color(int r, int g, int b) : Color(r, g, b, 255) {
	}
	Color::~Color() {
	}

	uint8_t Color::getR() const
	{
		return r;
	}

	uint8_t Color::getG() const
	{
		return g;
	}

	uint8_t Color::getB() const
	{
		return b;
	}

	uint8_t Color::getA() const
	{
		return a;
	}

	const Color Color::RED(255, 0, 0);
	const Color Color::ORANGE(255, 200, 0);
	const Color Color::YELLOW(255, 255, 0);
	const Color Color::GREEN(0, 255, 0);
	const Color Color::CYAN(0, 255, 255);
	const Color Color::BLUE(0, 0, 255);
	const Color Color::MAGENTA(255, 0, 255);
	const Color Color::WHITE(255, 255, 255);
	const Color Color::BLACK(0, 0, 0);
}
