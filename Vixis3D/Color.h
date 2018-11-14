#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace VIX {
	class Color
	{
	public:
		static const Color RED;
		static const Color ORANGE;
		static const Color YELLOW;
		static const Color GREEN;
		static const Color CYAN;
		static const Color BLUE;
		static const Color MAGENTA;
		static const Color WHITE;
		static const Color BLACK;

		Color(const Color & color);
		Color(int r, int g, int b, int a);
		Color(int r, int g, int b);
		~Color();

		uint8_t getR() const;
		uint8_t getG() const;
		uint8_t getB() const;
		uint8_t getA() const;
		
		inline uint32_t combined() const {
			return combinedVal;
		}

	private:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		uint32_t combinedVal;
	};
}
#endif

