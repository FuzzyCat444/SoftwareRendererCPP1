#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vec2.h"
#include "Vec3.h"
#include <vector>

namespace VIX {
	class Transform
	{
	public:
		Transform();
		~Transform();

		// 2D
		Transform * chain(Transform * other);

		void setScale2(const Vec2 & scale);

		void setTranslate2(const Vec2 & translate);

		void setRotate2(double rotate);

		Vec2 transform2(const Vec2 & v) const;
		
		// 3D
		void setScale3(const Vec3 & scale);

		void setTranslate3(const Vec3 & translate);

		void setRotate3(const Vec3 & rotate);

		void setPerspective3(double fovAngle);

		Vec3 transform3(const Vec3 & v, bool normal) const;

		Vec3 revTransform3(const Vec3 & v, bool normal) const;

		double getPerspectiveDivide() const;
	private:
		enum Type {
			NONE,
			SCALE2,
			TRANSLATE2,
			ROTATE2,
			SCALE3,
			TRANSLATE3,
			ROTATE3,
			PERSPECTIVE
		} type;

		Transform * next;

		Vec2 scale2;
		Vec2 translate2;
		double rotate2;

		Vec3 scale3;
		Vec3 translate3;
		Vec3 rotate3;

		double perspectiveDiv;
	};
}

#endif