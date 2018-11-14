#include "Vec2.h"

namespace VIX {
	Vec2::Vec2(double x, double y) : x(x), y(y) {
	}

	Vec2::Vec2(const Vec3 & v) : Vec2(v.x, v.y)
	{
	}

	Vec2::Vec2() : Vec2(0.0, 0.0) {
	}

	Vec2::~Vec2() {
	}
}
