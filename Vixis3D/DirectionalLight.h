#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Color.h"
#include "Vec3.h"
#include "Transform.h"

namespace VIX {
	class DirectionalLight {
	public:
		DirectionalLight();
		DirectionalLight(Color color, Vec3 direction);
		~DirectionalLight();

		double getBrightness(const Vec3& surfaceNormal, const Transform* t=nullptr) const;

		Vec3& getDirection();

		Vec3 getColor() const;
	private:
		Vec3 color; // Normalized color values
		Vec3 direction;
	};
}

#endif
