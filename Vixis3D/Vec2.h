#ifndef VEC2_H
#define VEC2_H

#include "Vec3.h"

namespace VIX {
	class Vec2 {
	public:
		Vec2(double x, double y);
		Vec2(const Vec3 & v);
		Vec2();
		~Vec2();

		double x;
		double y;
	};
}
#endif

