#ifndef FACE_H
#define FACE_H

#include "Vec3.h"
#include "Color.h"
#include "Vertex.h"

namespace VIX {
	class Face {
	public:
		Face(Vertex v1, Vertex v2, Vertex v3);
		~Face();

		Vertex v1;
		Vertex v2;
		Vertex v3;
		Vec3 surfaceNormal;
	};
}

#endif