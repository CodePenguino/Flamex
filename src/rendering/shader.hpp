#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../ecs/entity.hpp"

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertPath, const char* fragPath);
	void create(const char* vertPath, const char* fragPath);
	~Shader();

	inline GLuint getUniformLocation(const char* name) const { return glGetUniformLocation(id, name); }

	template<typename T>
	inline void update(ECS::Entity& camera, T& transform) {
		setMat4(u_transform, camera.get_component<CameraComponent>().getViewProj() * transform.getModel());
	}

	// Setter functions
	inline void setBool(const char* name, bool value) const { glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value)); }
	inline void setBool(GLuint loc, bool value) const { glUniform1i(loc, static_cast<int>(value)); }

	inline void setInt(const char* name, int value) const { glUniform1i(glGetUniformLocation(id, name), value); }
	inline void setInt(GLuint loc, int value) const { glUniform1i(loc, value); }

	inline void setFloat(const char* name, float value) const { glUniform1f(glGetUniformLocation(id, name), value); }
	inline void setFloat(GLuint loc, float value) const { glUniform1f(loc, value); }

	inline void setVec2(const char* name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(id, name), 1, &value[0]); }
	inline void setVec2(GLuint loc, const glm::vec2& value) const { glUniform2fv(loc, 1, &value[0]); }
	inline void setVec2(const char* name, float x, float y) const { glUniform2f(glGetUniformLocation(id, name), x, y); }
	inline void setVec2(GLuint loc, float x, float y) const { glUniform2f(loc, x, y); }

	inline void setVec3(const char* name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(id, name), 1, &value[0]); }
	inline void setVec3(GLuint loc, const glm::vec3& value) const { glUniform3fv(loc, 1, &value[0]); }
	inline void setVec3(const char* name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(id, name), x, y, z); }
	inline void setVec3(GLuint loc, float x, float y, float z) const { glUniform3f(loc, x, y, z); }

	inline void setVec4(const char* name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(id, name), 1, &value[0]); }
	inline void setVec4(GLuint loc, const glm::vec4& value) const { glUniform4fv(loc, 1, &value[0]); }
	inline void setVec4(const char* name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(id, name), x, y, z, w); }
	inline void setVec4(GLuint loc, float x, float y, float z, float w) const { glUniform4f(loc, x, y, z, w); }

	inline void setMat2(const char* name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]); }
	inline void setMat2(GLuint loc, const glm::mat2& mat) const { glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]); }

	inline void setMat3(const char* name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]); }
	inline void setMat3(GLuint loc, const glm::mat3& mat) const { glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]); }

	inline void setMat4(const char* name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]); }
	inline void setMat4(GLuint loc, const glm::mat4& mat) const { glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]); }

	GLuint id;

private:
	GLuint u_transform;
};
