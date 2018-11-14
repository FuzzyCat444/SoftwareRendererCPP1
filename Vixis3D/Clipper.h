#ifndef CLIPPER_H
#define CLIPPER_H

#include "Vertex.h"

#include <array>

namespace VIX {
	class Clipper {
	public:
		enum Result {
			UNCLIPPED,
			CLIPPED_1,
			CLIPPED_2,
			REMOVED
		};

		Clipper();
		~Clipper();

		Result clip(Vertex v1, Vertex v2, Vertex v3);

		const std::array<Vertex, 3> & getTri1() const;
		const std::array<Vertex, 3> & getTri2() const;
	private:
		std::array<Vertex, 3> tri1;
		std::array<Vertex, 3> tri2;

		static const double NEAR_CLIP;
	};
}

#endif
