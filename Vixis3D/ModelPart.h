#ifndef MODELPART_H
#define MODELPART_H

#include <vector>

#include "Vec3.h"
#include "Material.h"
#include "Face.h"

namespace VIX {
	struct ModelPart {
	public:
		ModelPart(const Material & material);
		ModelPart();

		std::vector<Face> faces;

		Material material;
	};
}

#endif