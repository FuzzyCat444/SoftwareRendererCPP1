#include "Transform.h"

#include "MathConstants.h"
#include <cmath>

namespace VIX {
	Transform::Transform() : next(nullptr), scale2(1.0, 1.0), translate2(), rotate2(0.0), scale3(1.0, 1.0, 1.0), translate3(), rotate3(), perspectiveDiv(1.0), type(Type::NONE)
	{

	}

	Transform::~Transform()
	{
	}

	Transform * Transform::chain(Transform * other) 
	{
		next = other;
		return other;
	}

	void Transform::setScale2(const Vec2 & scale)
	{
		this->scale2 = scale;
		type = Type::SCALE2;
	}

	void Transform::setTranslate2(const Vec2 & translate)
	{
		this->translate2 = translate;
		type = Type::TRANSLATE2;
	}

	void Transform::setRotate2(double rotate)
	{
		this->rotate2 = rotate;
		type = Type::ROTATE2;
	}

	Vec2 Transform::transform2(const Vec2 & v) const
	{
		Vec2 vec(v);

		switch (type) {
		case Type::SCALE2:
		{
			vec.x *= scale2.x;
			vec.y *= scale2.y;
		}
			break;
		case Type::TRANSLATE2:
		{
			vec.x += translate2.x;
			vec.y += translate2.y;
		}
			break;
		case Type::ROTATE2:
		{
			double tmpX = vec.x;
			double tmpY = vec.y;
			double angle = rotate2 * PI / 180.0;
			vec.x = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.y = tmpX * std::sin(angle) + tmpY * std::cos(angle);
		}
			break;
		default:
			break;
		}

		return next != nullptr ? next->transform2(vec) : vec;
	}

	void Transform::setScale3(const Vec3 & scale)
	{
		this->scale3 = scale;
		type = Type::SCALE3;
	}

	void Transform::setTranslate3(const Vec3 & translate)
	{
		this->translate3 = translate;
		type = Type::TRANSLATE3;
	}

	void Transform::setRotate3(const Vec3 & rotate)
	{
		this->rotate3 = rotate;
		type = Type::ROTATE3;
	}

	void Transform::setPerspective3(double fovAngle)
	{
		perspectiveDiv = std::tan(fovAngle * PI / 180.0 / 2.0);
		type = Type::PERSPECTIVE;
	}

	Vec3 Transform::transform3(const Vec3 & v, bool normal) const
	{
		Vec3 vec(v);

		switch (type) {
		case Type::SCALE3:
		{
			vec.x *= scale3.x;
			vec.y *= scale3.y;
			vec.z *= scale3.z;
			if (normal) {
				double dist = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				vec.x /= dist;
				vec.y /= dist;
				vec.z /= dist;
			}
		}
			break;
		case Type::TRANSLATE3:
		{
			if (!normal) {
				vec.x += translate3.x;
				vec.y += translate3.y;
				vec.z += translate3.z;
			}
		}
			break;
		case Type::ROTATE3:
		{
			// Z Rotation
			double tmpX = vec.x;
			double tmpY = vec.y;
			double angle = rotate3.z * PI / 180.0;
			vec.x = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.y = tmpX * std::sin(angle) + tmpY * std::cos(angle);

			// Y Rotation
			tmpX = vec.x;
			tmpY = vec.z;
			angle = rotate3.y * PI / 180.0;
			vec.x = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.z = tmpX * std::sin(angle) + tmpY * std::cos(angle);

			// X Rotation
			tmpX = vec.z;
			tmpY = vec.y;
			angle = rotate3.x * PI / 180.0;
			vec.z = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.y = tmpX * std::sin(angle) + tmpY * std::cos(angle);
		}
			break;
		case Type::PERSPECTIVE:
		{
			if (!normal) {
				double zx = vec.z * perspectiveDiv;
				vec.x /= zx;
				vec.y /= zx;
			}
		}
			break;
		default:
			break;
		}

		return next != nullptr ? next->transform3(vec, normal) : vec;
	}

	Vec3 Transform::revTransform3(const Vec3 & v, bool normal) const
	{
		Vec3 vec = next != nullptr ? next->revTransform3(v, normal) : v;

		switch (type) {
		case Type::SCALE3:
		{
			vec.x /= scale3.x;
			vec.y /= scale3.y;
			vec.z /= scale3.z;
			if (normal) {
				double dist = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				vec.x /= dist;
				vec.y /= dist;
				vec.z /= dist;
			}
		}
		break;
		case Type::TRANSLATE3:
		{
			if (!normal) {
				vec.x -= translate3.x;
				vec.y -= translate3.y;
				vec.z -= translate3.z;
			}
		}
		break;
		case Type::ROTATE3:
		{
			// Z Rotation
			double tmpX = vec.x;
			double tmpY = vec.y;
			double angle = -rotate3.z * PI / 180.0;
			vec.x = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.y = tmpX * std::sin(angle) + tmpY * std::cos(angle);

			// Y Rotation
			tmpX = vec.x;
			tmpY = vec.z;
			angle = -rotate3.y * PI / 180.0;
			vec.x = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.z = tmpX * std::sin(angle) + tmpY * std::cos(angle);

			// X Rotation
			tmpX = vec.z;
			tmpY = vec.y;
			angle = -rotate3.x * PI / 180.0;
			vec.z = tmpX * std::cos(angle) - tmpY * std::sin(angle);
			vec.y = tmpX * std::sin(angle) + tmpY * std::cos(angle);
		}
		break;
		case Type::PERSPECTIVE:
		{
			if (!normal) {
				double zx = vec.z * perspectiveDiv;
				vec.x *= zx;
				vec.y *= zx;
			}
		}
		break;
		default:
			break;
		}

		return vec;
	}

	double Transform::getPerspectiveDivide() const
	{
		return perspectiveDiv;
	}
}
