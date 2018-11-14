#ifndef VERTEX_H
#define VERTEX_H

#include "Vec3.h"
#include "Vec2.h"

namespace VIX {
	class Vertex {
	public:
		Vertex();
		Vertex(Vec3 xyz, Vec2 uv = Vec2(0.0, 0.0), Vec3 normal = Vec3(0.0, 0.0, 0.0));
		~Vertex();

		Vec3 xyz;
		Vec2 uv;
		Vec3 normal;
	};
}

#endif