#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Math
{
	struct Quaternion;

	typedef glm::vec2 Vector2f;
	typedef glm::vec3 Vector3f;
	typedef glm::vec4 Vector4f;
	
	typedef glm::ivec2 Vector2i;
	typedef glm::ivec3 Vector3i;
	typedef glm::ivec4 Vector4i;

	typedef glm::mat2 Matrix2f;
	typedef glm::mat3 Matrix3f;
	typedef glm::mat4 Matrix4f;

	// Vector printing operator
	template<glm::length_t L, typename T, glm::qualifier Q>
	std::ostream& operator<<(std::ostream& stream, glm::vec<L,T,Q> const& vec)
	{
		uint8_t i;

		for(i = 0; i < vec.length() - 1; i++)
		{
			stream << vec[i] << ", ";
		}

		stream << vec[i++];
		return stream;
	}

	// Quaternion printing operator
	std::ostream& operator<<(std::ostream& stream, const Quaternion& quat);

	// glm::quat, but better
	struct Quaternion : glm::quat
	{
		Quaternion() { x = 0; y = 0; z = 0; w = 1; };
		Quaternion(const glm::quat& q);
		Quaternion(float x, float y, float z, float w);
		
		template <typename T>
		void operator=(const T& q) { x = q.x; y = q.y; z = q.z; w = q.w; }

		void operator*=(const Quaternion& q);

		// Euler rotation in YXZ order
		void euler(const Vector3f& euler);
		// YXZ euler rotation
		void euler_yxz(const Vector3f& euler);
		
		// Angle axis quaternion rotation
		inline void angle_axis(float angle, const Vector3f& axis) { *this = glm::angleAxis(glm::radians(angle), axis); }

		// Get the forward direction of a quaternion
		inline Vector3f get_forward() const { return glm::rotate(*this, glm::vec3(0,0,1)); }
		// Get the back direction of a quaternion
		inline Vector3f get_back() const { return glm::rotate(*this, glm::vec3(0,0,-1)); }

		// Get the up direction of a quaternion
		inline Vector3f get_up() const { return glm::rotate(*this, glm::vec3(0,1,0)); }
		// Get the down direction of a quaternion
		inline Vector3f get_down() const { return glm::rotate(*this, glm::vec3(0,-1,0)); }

		// Get the right direction of a quaternion
		inline Vector3f get_right() const { return glm::rotate(*this, glm::vec3(1,0,0)); }
		// Get the left direction of a quaternion
		inline Vector3f get_left() const { return glm::rotate(*this, glm::vec3(-1,0,0)); }

		// Returns a quaternion when converted to a euler angle
		inline Vector3f to_euler() const { return glm::degrees(glm::eulerAngles(*this)); }
	};

	// Rotate quaternion with euler angles
	Quaternion rotate(const Quaternion& q, const Vector3f& euler, bool local = true);
	// Rotate quaternion with angle axis
	Quaternion rotate(const Quaternion& q, float angle, const Vector3f& axis, bool local = true);

	// Convert a quaternion to a Vector4f
	inline Vector4f toVec4(const Quaternion& q) { return Vector4f(q.x, q.y, q.z, q.w); }

	inline Quaternion angle_axis(float angle, const Vector3f& axis)
	{ return glm::angleAxis(glm::radians(angle), axis); }

	Quaternion euler_yxz(const Vector3f& euler);
	inline Quaternion euler(const Vector3f& euler) { return euler_yxz(euler); }
};
