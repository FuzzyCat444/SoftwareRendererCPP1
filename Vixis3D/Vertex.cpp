#include "Vertex.h"

namespace VIX {
	Vertex::Vertex()
	{
	}
	Vertex::Vertex(Vec3 xyz, Vec2 uv, Vec3 normal) : xyz(xyz), uv(uv), normal(normal)
	{
	}
	Vertex::~Vertex()
	{
	}
}
