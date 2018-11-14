
#include "Vec3.h"
#include <cmath>

namespace VIX {

	Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {
	}

	Vec3::Vec3() : Vec3(0.0, 0.0, 0.0) {
	}

	Vec3::~Vec3() {

	}
	double Vec3::dot(const Vec3 & v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	double Vec3::length()
	{
		return sqrt(dot(*this));
	}
	Vec3 Vec3::cross(const Vec3& other)
	{
		Vec3 n;
		n.x = y * other.z - z * other.y;
		n.y = z * other.x - x * other.z;
		n.z = x * other.y - y * other.x;
		return n;
	}
	void Vec3::normalize()
	{
		double len = length();
		x /= len;
		y /= len;
		z /= len;
	}
}