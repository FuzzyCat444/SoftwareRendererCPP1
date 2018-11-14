#include "DirectionalLight.h"

#include <cstdio>
#include <cmath>

namespace VIX {
	DirectionalLight::DirectionalLight() {
	
	}

	DirectionalLight::DirectionalLight(Color color, Vec3 direction) :
		color(color.getR() / 255.0, color.getG() / 255.0, color.getB() / 255.0),
		direction(direction)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	double DirectionalLight::getBrightness(const Vec3& surfaceNormal, const Transform* t) const {
		Vec3 dirTransformed = t == nullptr ? direction : t->revTransform3(direction, true);
		Vec3 toLight(-dirTransformed.x, -dirTransformed.y, -dirTransformed.z);

		double distSq = toLight.dot(toLight);

		double dot = toLight.dot(surfaceNormal);
		double brightness = dot / sqrt(distSq);

		return brightness < 0.0 ? 0.0 : brightness;
	}

	Vec3 DirectionalLight::getColor() const {
		return color;
	}

	Vec3& DirectionalLight::getDirection() {
		return direction;
	}
}
