#include "Clipper.h"

#include <utility>

namespace VIX {
	Clipper::Clipper() {

	}

	Clipper::~Clipper() {

	}

	Clipper::Result Clipper::clip(Vertex v1, Vertex v2, Vertex v3) {
		if (v2.xyz.z < v1.xyz.z) std::swap(v1, v2);
		if (v3.xyz.z < v1.xyz.z) std::swap(v1, v3);
		if (v3.xyz.z < v2.xyz.z) std::swap(v2, v3);

		Result result;

		if (v1.xyz.z >= NEAR_CLIP) {
			result = UNCLIPPED;
		}
		else if (v3.xyz.z < NEAR_CLIP) {
			result = REMOVED;
		}
		else if (v2.xyz.z >= NEAR_CLIP) {	// Clip behind middle vertex
			// Clip from v1 to v2, v1 to v3
			double t1 = (NEAR_CLIP - v1.xyz.z) / (v2.xyz.z - v1.xyz.z);
			Vertex p1(Vec3(v1.xyz.x + t1 * (v2.xyz.x - v1.xyz.x),
						   v1.xyz.y + t1 * (v2.xyz.y - v1.xyz.y),
						   v1.xyz.z + t1 * (v2.xyz.z - v1.xyz.z)),
					  Vec2(v1.uv.x + t1 * (v2.uv.x - v1.uv.x), 
						   v1.uv.y + t1 * (v2.uv.y - v1.uv.y)));
			double t2 = (NEAR_CLIP - v1.xyz.z) / (v3.xyz.z - v1.xyz.z);
			Vertex p2(Vec3(v1.xyz.x + t2 * (v3.xyz.x - v1.xyz.x),
						   v1.xyz.y + t2 * (v3.xyz.y - v1.xyz.y),
						   v1.xyz.z + t2 * (v3.xyz.z - v1.xyz.z)),
					  Vec2(v1.uv.x + t2 * (v3.uv.x - v1.uv.x),
					       v1.uv.y + t2 * (v3.uv.y - v1.uv.y)));
			tri1[0] = p1;
			tri1[1] = v2;
			tri1[2] = v3;

			tri2[0] = p1;
			tri2[1] = v3;
			tri2[2] = p2;

			result = CLIPPED_2;
		}
		else {	// Clip in front of middle vertex
			// Clip from v2 to v3, v1 to v3
			double t1 = (NEAR_CLIP - v2.xyz.z) / (v3.xyz.z - v2.xyz.z);
			Vertex p1(Vec3(v2.xyz.x + t1 * (v3.xyz.x - v2.xyz.x),
						   v2.xyz.y + t1 * (v3.xyz.y - v2.xyz.y),
						   v2.xyz.z + t1 * (v3.xyz.z - v2.xyz.z)),
					  Vec2(v2.uv.x + t1 * (v3.uv.x - v2.uv.x),
						   v2.uv.y + t1 * (v3.uv.y - v2.uv.y)));
			double t2 = (NEAR_CLIP - v1.xyz.z) / (v3.xyz.z - v1.xyz.z);
			Vertex p2(Vec3(v1.xyz.x + t2 * (v3.xyz.x - v1.xyz.x),
						   v1.xyz.y + t2 * (v3.xyz.y - v1.xyz.y),
						   v1.xyz.z + t2 * (v3.xyz.z - v1.xyz.z)),
					  Vec2(v1.uv.x + t2 * (v3.uv.x - v1.uv.x),
						   v1.uv.y + t2 * (v3.uv.y - v1.uv.y)));
			tri1[0] = p1;
			tri1[1] = v3;
			tri1[2] = p2;

			result = CLIPPED_1;
		}
		return result;
	}

	const std::array<Vertex, 3> & Clipper::getTri1() const {
		return tri1;
	}

	const std::array<Vertex, 3> & Clipper::getTri2() const {
		return tri2;
	}

	const double Clipper::NEAR_CLIP = 0.1;
}
