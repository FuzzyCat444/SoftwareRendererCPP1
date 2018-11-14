
#ifndef VEC3_H
#define VEC3_H

namespace VIX {
	class Vec3 {
	public:
		Vec3(double x, double y, double z);
		Vec3();
		~Vec3();

		double dot(const Vec3& v);
		double length();
		Vec3 cross(const Vec3& other);
		void normalize();

		double x;
		double y;
		double z;
	};
}

#endif