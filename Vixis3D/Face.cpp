#include "Face.h"

namespace VIX {
	Face::Face(Vertex v1, Vertex v2, Vertex v3) : v1(v1), v2(v2), v3(v3) {
		Vec3 a(v3.xyz.x - v2.xyz.x, v3.xyz.y - v2.xyz.y, v3.xyz.z - v2.xyz.z);
		Vec3 b(v1.xyz.x - v2.xyz.x, v1.xyz.y - v2.xyz.y, v1.xyz.z - v2.xyz.z);
		surfaceNormal = a.cross(b);
		surfaceNormal.normalize();
	}

	Face::~Face() {
	}
}
