#ifndef EDGE_H
#define EDGE_H

#include <cmath>
#include <iostream>

#include "Vertex.h"
#include "Vec3.h"

namespace VIX {
	class Edge {
	public:
		enum Axis {
			X,
			Y
		};

		Edge();
		~Edge();

		inline void set(const Vertex & a, const Vertex & b, const Vec3 & col1, const Vec3 & col2, double start, double inc, Axis axis, double p) {
			col = col1;
			this->axis = axis;
			this->p = p;
			double z0 = a.xyz.z, z1 = b.xyz.z;
			double c0, c1;
			switch (axis) {
			case Axis::X:
				c0 = a.xyz.x;
				c1 = b.xyz.x;
				break;
			case Axis::Y:
				c0 = a.xyz.y;
				c1 = b.xyz.y + 0.0000001; // Cheap fix to find avoid division by zero
				break;
			default: break;
			}

			double denom = b.xyz.z * c0 - a.xyz.z * c1;
			double pZDiff = p * (z1 - z0);

			// For interpolating the z value
			oneOverZ = (start * pZDiff + c0 - c1) / denom;
			z = 1.0 / oneOverZ;
			incZ = inc * pZDiff / denom;

			// For interpolating the c value
			c = start * p * z;
			cUnp = start * p;	// The unprojected c value (perspective divide constant 'p' already computed)
			this->inc = inc * p;

			double u0 = a.uv.x, u1 = b.uv.x;
			double v0 = a.uv.y, v1 = b.uv.y;

			// For interpolating uv
			double dc = c1 - c0;
			incU = (u1 - u0) / dc;
			incV = (v1 - v0) / dc;
			double stepC = c - c0; // How far c started past the original vertex c
			u = u0 + stepC * incU;
			v = v0 + stepC * incV;

			// For interpolating color (for lights mainly)
			incR = (col2.x - col1.x) / dc;
			incG = (col2.y - col1.y) / dc;
			incB = (col2.z - col1.z) / dc;
			col.x = col1.x + stepC * incR;
			col.y = col1.y + stepC * incG;
			col.z = col1.z + stepC * incB;
		}

		inline void step() {
			oneOverZ += incZ;
			z = 1.0 / oneOverZ;

			double prevC = c;
			cUnp += inc;
			c = cUnp * z;
			double dc = c - prevC;

			u += incU * dc;
			v += incV * dc;

			col.x += incR * dc;
			col.y += incG * dc;
			col.z += incB * dc;
		}

		inline double getU() const {
			return u;
		}

		inline double getV() const {
			return v;
		}

		inline double getZ() const {
			return z;
		}

		inline double getR() const {
			return col.x;
		}

		inline double getG() const {
			return col.y;
		}

		inline double getB() const {
			return col.z;
		}
	private:
		double uBefore;
		double cUnp;
		double inc;

		Axis axis;
		double p;

		double incZ;
		double oneOverZ;

		double c;
		double z;

		double incU;
		double incV;
		double u;
		double v;

		double incR;
		double incG;
		double incB;
		Vec3 col;
	};
}

#endif
