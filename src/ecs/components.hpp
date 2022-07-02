#pragma once

#include "../core/math.hpp"
#include <glad/glad.h>
#include <glm/gtx/transform.hpp>
#include "../core/window.hpp"

struct Transform2DComponent
{
	Transform2DComponent(const Math::Vector2f& pos = Math::Vector2f(), const float rot = 0.0f, const Math::Vector2f& scale = Math::Vector2f(1,1)) :
		position(pos), rotation(rot), scale(scale) {}

	// Returns the model matrix of the transform
	inline glm::mat4 getModel() const
	{
		const glm::mat4 posMatrix = glm::translate(glm::vec3(position, 0.0f));
		const glm::mat4 rotMatrix = glm::rotate(glm::radians(rotation), glm::vec3(0,0,1));
		const glm::mat4 sclMatrix = glm::scale(glm::vec3(scale, 1.0f));

		return posMatrix * rotMatrix * sclMatrix;
	}

	inline void lookAt(const Math::Vector2f& p) { rotation = glm::degrees(atan2f(p.y, p.x)); }

	Math::Vector2f position, scale;
	float rotation;
};

struct Transform3DComponent
{
	Transform3DComponent(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1,0,0,0), const glm::vec3& scale = glm::vec3(1,1,1)) :
		position(pos), rotation(rot), scale(scale) {}

	// Returns the model matrix of the transform
	inline glm::mat4 getModel() const
	{
		const glm::mat4 posMatrix = glm::translate(position);
		const glm::mat4 sclMatrix = glm::scale(scale);

		return posMatrix * glm::mat4_cast(rotation) * sclMatrix;
	}

	void lookAt(const Math::Vector3f& p);

	Math::Vector3f position, scale;
	Math::Quaternion rotation;
};

struct CameraComponent
{
	// To actually initialize the camera, use the init functions.
	CameraComponent() :
		projection(glm::mat4(1.0f)), fov(70.0f), zNear(0.03f), zFar(100.0f) {}

	// Orthographic
	inline void init_ortho(const glm::vec3& pos, float zNear = 0.03f, float zFar = 100.0f)
	{
		projection = glm::ortho(-window.aspect_ratio, window.aspect_ratio, -1.0f, 1.0f, zNear, zFar);
		transform.position = pos;
		this->zNear = zNear;
		this->zFar = zFar;
	}

	// Perspective
	inline void init_perspective(const glm::vec3& pos, float fov = 70.0f, float zNear = 0.03f, float zFar = 100.0f)
	{
		projection = glm::perspective(fov, window.aspect_ratio, zNear, zFar);
		transform.position = pos;
		this->fov = fov;
		this->zNear = zNear;
		this->zFar = zFar;
	}

	inline void update_ortho() { projection = glm::ortho(-window.aspect_ratio, window.aspect_ratio, -1.0f, 1.0f, zNear, zFar); }
	inline void update_perspective() { projection = glm::perspective(fov, window.aspect_ratio, zNear, zFar); }

	inline glm::mat4 getViewProj() const
	{
		const glm::mat4 pos = glm::translate(glm::mat4(1.0f),
				glm::vec3(-transform.position.x, -transform.position.y, transform.position.z));

		const glm::quat rotX = glm::angleAxis(glm::radians(transform.rotation.x), glm::vec3(1,0,0));
		const glm::quat rotY = glm::angleAxis(glm::radians(transform.rotation.y), glm::vec3(0,1,0));
		const glm::quat rotZ = glm::angleAxis(glm::radians(transform.rotation.z), glm::vec3(0,0,1));

		return projection * (glm::mat4_cast(rotZ*rotX*rotY) * pos);
	}

	glm::mat4 projection;
	Transform3DComponent transform;
	float fov, zNear, zFar;
};

class TextureComponent
{
public:
	void create(const char* filePath);
	inline ~TextureComponent() { glDeleteTextures(1, &m_texture); }

	inline void bind(uint8_t unit) const
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	int width, height;

private:
	GLuint m_texture;
};

struct SpriteComponent
{
	SpriteComponent() = default;
	inline SpriteComponent(const char* texturePath, float resolution = 360) { create(texturePath, resolution); }
	inline ~SpriteComponent() { destroy(); }

	void create(const char* texturePath, float resolution = 360);
	void destroy();

	TextureComponent texture;
	GLuint vao, vbo, ebo;
};
