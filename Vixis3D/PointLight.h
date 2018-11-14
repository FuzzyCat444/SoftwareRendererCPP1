#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Color.h"
#include "Vec3.h"
#include "Transform.h"

namespace VIX {
	class PointLight {
	public:
		PointLight();
		PointLight(Color color, double radius, Vec3 pos);
		~PointLight();

		double getBrightness(const Vec3& surfaceNormal, const Vec3& point, const Transform* t=nullptr) const;

		void setPos(Vec3 pos);

		Vec3 getPos() const;

		Vec3 getColor() const;
	private:
		Vec3 color; // Normalized color values
		double radiusSquared;
		Vec3 pos;
	};
}

#endif
