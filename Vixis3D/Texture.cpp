#include "Texture.h"

#include <algorithm>

#include "Color.h"
#include "MathFunctions.h"

namespace VIX {
	Texture::Texture() : pixels(nullptr), width(-1), height(-1)
	{
	}
	Texture::Texture(uint32_t * pixels, int width, int height) : pixels(pixels), width(width), height(height)
	{
	}

	Texture::~Texture()
	{
	}

	uint32_t * Texture::getPixels() const
	{
		return pixels;
	}

	uint32_t Texture::getPixelAt(double u, double v)
	{
		int x = fastFloor(u);
		int y = fastFloor(v);

		if (x < 0 || x >= width || y < 0 || y >= height) {
			x = (x % width + width) % width;
			y = (y % height + height) % height;
		}

		return pixels[x + y * width];
	}

	int Texture::getWidth() const
	{
		return width;
	}

	int Texture::getHeight() const
	{
		return height;
	}

	bool Texture::isNull() const
	{
		return pixels == nullptr || width == -1 || height == -1;
	}
}
