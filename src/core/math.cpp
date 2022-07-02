#include "math.hpp"

namespace Math
{

std::ostream& operator<<(std::ostream& stream, const Quaternion& quat)
{
	uint8_t i;

	for(i = 0; i < 3; i++)
	{
		stream << quat[i] << ", ";
	}

	stream << quat[i++];
	return stream;
}

Quaternion::Quaternion(const glm::quat& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Quaternion::operator*=(const Quaternion& q)
{
	*this = *this * q;
}

void Quaternion::euler(const Vector3f& euler)
{
	euler_yxz(euler);
}

// convert a YXZ euler rotation into a quaternion
void Quaternion::euler_yxz(const Vector3f& euler)
{
	// If it works, it works...
	*this = Math::angle_axis(euler.y, Vector3f(0,1,0)) * 
	        Math::angle_axis(euler.x, Vector3f(1,0,0)) *
	        Math::angle_axis(euler.z, Vector3f(0,0,1));
}

Quaternion rotate(Quaternion& q, const Vector3f& euler, bool local)
{
	if(local) {
		q *= Math::angle_axis(euler.x, Vector3f(1,0,0));
		q *= Math::angle_axis(euler.y, Vector3f(0,1,0));
		q *= Math::angle_axis(euler.z, Vector3f(0,0,1));
	}
	// Same as local rotation, but with some extra code to cancel out the quaternion's offsets
	else {
		q *= Math::angle_axis(euler.x, glm::rotate(glm::conjugate(q), Vector3f(1,0,0)));
		q *= Math::angle_axis(euler.y, glm::rotate(glm::conjugate(q), Vector3f(0,1,0)));
		q *= Math::angle_axis(euler.z, glm::rotate(glm::conjugate(q), Vector3f(0,0,1)));
	}

	return q;
}

Quaternion rotate(Quaternion& q, float angle, const Vector3f& axis, bool local)
{
	if(local) {
		q *= Math::angle_axis(angle, axis);
	}
	// Same as local rotation, but with some extra code to cancel out the quaternion's offsets
	else {
		q *= Math::angle_axis(angle, glm::rotate(glm::conjugate(q), axis));
	}

	return q;
}

Quaternion euler_yxz(const Vector3f& euler)
{
	return Quaternion(Math::angle_axis(euler.y, Vector3f(0,1,0)) * 
	                  Math::angle_axis(euler.x, Vector3f(1,0,0)) *
	                  Math::angle_axis(euler.z, Vector3f(0,0,1)));
}

};
