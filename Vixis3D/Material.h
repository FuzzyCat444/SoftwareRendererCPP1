#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

namespace VIX {
	struct Material {
	public:
		Material(const Texture & texture);
		Material();

		Texture texture;
	};
}

#endif