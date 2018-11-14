#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include <vector>

namespace VIX {
	class Texture {
	public:
		Texture();
		Texture(uint32_t * pixels, int width, int height);
		~Texture();

		uint32_t * getPixels() const;

		uint32_t getPixelAt(double u, double v);

		int getWidth() const;

		int getHeight() const;

		bool isNull() const;
	private:
		uint32_t * pixels;
		int width;
		int height;
	};
}

#endif