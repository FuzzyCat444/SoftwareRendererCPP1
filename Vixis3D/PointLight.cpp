#include "PointLight.h"

#include <cstdio>
#include <cmath>

namespace VIX {
	PointLight::PointLight() {

	}

	PointLight::PointLight(Color color, double radius, Vec3 pos) :
		color(color.getR() / 255.0, color.getG() / 255.0, color.getB() / 255.0),
		radiusSquared(radius * radius),
		pos(pos)
	{
	}

	PointLight::~PointLight()
	{
	}

	double PointLight::getBrightness(const Vec3& surfaceNormal, const Vec3& point, const Transform* t) const {
		Vec3 posTransformed = t == nullptr ? pos : t->revTransform3(pos, false);
		Vec3 toLight(posTransformed.x - point.x, posTransformed.y - point.y, posTransformed.z - point.z);

		double distSquared = toLight.dot(toLight);

		if (distSquared < radiusSquared) {
			double rSq = distSquared / radiusSquared;
			double attenuation = (1.0 - rSq) * (1.0 - rSq);	// Using (1-r^2)^2 for attenuation

			double dist = sqrt(distSquared);
			double dot = toLight.dot(surfaceNormal);
			double brightness = dot * attenuation / dist;

			return brightness < 0.0 ? 0.0 : brightness;
		}
		return 0.0;
	}

	void PointLight::setPos(Vec3 pos) {
		this->pos = pos;
	}

	Vec3 PointLight::getPos() const {
		return pos;
	}

	Vec3 PointLight::getColor() const {
		return color;
	}
}
