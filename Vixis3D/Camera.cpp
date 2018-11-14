#include "Camera.h"
#include <cmath>

namespace VIX {
	Camera::Camera()
	{
		rotationTransform.chain(&positionTransform);
	}

	Camera::~Camera()
	{
	}

	void Camera::setPosition(const Vec3& pos)
	{
		position = pos;
	}

	void Camera::setRotation(const Vec3& rot)
	{
		rotation = rot;
	}

	void Camera::move(const Vec3& v)
	{
		position.x += v.x;
		position.y += v.y;
		position.z += v.z;
	}

	void Camera::moveForward(double amt)
	{
		Vec3 dir(0.0, 0.0, 1.0);
		dir = rotationTransform.transform3(dir, true);
		position.x += dir.x * amt;
		position.y += dir.y * amt;
		position.z += dir.z * amt;
	}

	void Camera::rotate(const Vec3& v)
	{
		rotation.x += v.x;
		rotation.y += v.y;
		rotation.z += v.z;
	}

	Vec3 Camera::getPosition()
	{
		return position;
	}

	Vec3 Camera::getRotation()
	{
		return rotation;
	}

	Vec3 Camera::transformPoint(const Vec3 & v, bool normal)
	{
		rotationTransform.setRotate3(rotation);
		positionTransform.setTranslate3(position);
		return rotationTransform.revTransform3(v, normal);
	}

	Vertex Camera::transformVertex(const Vertex & vt)
	{
		Vertex ret = vt;
		ret.xyz = transformPoint(ret.xyz, false);
		ret.normal = transformPoint(ret.normal, true);
		return ret;
	}

	const Transform & Camera::getTransform()
	{
		return rotationTransform;
	}
}
