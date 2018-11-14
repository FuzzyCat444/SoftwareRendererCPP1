#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"
#include "Vec3.h"
#include "Vertex.h"

namespace VIX {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void setPosition(const Vec3& pos);
		void setRotation(const Vec3& rot);

		void move(const Vec3& v);
		void moveForward(double amt);
		void rotate(const Vec3& v);

		Vec3 getPosition();
		Vec3 getRotation();

		Vec3 transformPoint(const Vec3& v, bool normal);

		Vertex transformVertex(const Vertex& vt);

		const Transform& getTransform();
	private:
		Vec3 position;
		Vec3 rotation;

		Transform positionTransform;
		Transform rotationTransform;
	};
}

#endif

