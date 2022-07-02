#include "components.hpp"
#include "../rendering/stb_image.h"
#include "../rendering/renderer.hpp"

using namespace Math;

static Quaternion safeQuatLookAt(const Vector3f& lookFrom, const Vector3f& lookTo, const Vector3f& up, const Vector3f& altUp)
{
	glm::vec3 direction = lookTo - lookFrom;
	const float directionLength = glm::length(direction);

	// Is the direction valid?
	if(!(directionLength > 0.0001f))
		return glm::quat(1,0,0,0);

	// Vector normalization
	direction /= directionLength;

	// Is the normal up parallel to direction
	if(glm::abs(glm::dot(direction, up)) > 0.9999f)
		return glm::quatLookAt(direction, altUp);
	else
		return glm::quatLookAt(direction, up);
}

void Transform3DComponent::lookAt(const Math::Vector3f& p)
{
	rotation = safeQuatLookAt(position, p, Vector3f(0,1,0), Vector3f(1,0,0));
}

void TextureComponent::create(const char* filePath)
{
	stbi_set_flip_vertically_on_load(true);
	int nrChannels;
	unsigned char* imageData = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if(!imageData)
	{
		std::cerr << "Error: Failed to load image: " << filePath << '\n';
		return;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

// NOTE: This is extremely dumb
// This is just so a calculation in the SpriteComponent.create function is forced to be constexpr
constexpr float calc_sprite_res(const float res)
{
	return 1.0f/res;
}

void SpriteComponent::create(const char* texturePath, float resolution)
{
	// Texture setup
	texture.create(texturePath);

	resolution = calc_sprite_res(resolution);

	const float scale_x = resolution * texture.width;
	const float scale_y = resolution * texture.height;

	// TODO: Change the sprite size depending on the texture size.
	const float sprite_vertices[16] = {
		// positions    // texcoords
	    /*0.5f,  0.5f,    1.0f, 1.0f,
	    0.5f, -0.5f,    1.0f, 0.0f,
	   -0.5f, -0.5f,    0.0f, 0.0f,
	   -0.5f,  0.5f,    0.0f, 1.0f*/

	   scale_x,  scale_y,    1.0f, 1.0f,
	   scale_x, -scale_y,    1.0f, 0.0f,
	  -scale_x, -scale_y,    0.0f, 0.0f,
	  -scale_x,  scale_y,    0.0f, 1.0f
	};

	constexpr unsigned short sprite_indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	// Set up OpenGL buffers and vertex array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_vertices), sprite_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite_indices), sprite_indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteComponent::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
