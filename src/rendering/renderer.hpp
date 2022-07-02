#pragma once

#include "shader.hpp"
#include "../ecs/entity.hpp"

namespace ECS
{
	class Entity;
};

namespace Renderer2D
{
	static float sprite_resolution = 1.0f/360.0f;
	static ECS::Entity* current_camera;
	static Shader* current_shader;

	// "Setter" functions
	static void use_camera(ECS::Entity& camera) { current_camera = &camera; }
	static void use_shader(Shader& shader) { glUseProgram(shader.id); current_shader = &shader; }

	// Draw an entity that has a sprite component
	static void draw(ECS::Entity& entity)
	{
		SpriteComponent& sprite = entity.get_component<SpriteComponent>();

		current_shader->update(*current_camera, entity.get_component<Transform3DComponent>());
		sprite.texture.bind(0);
		glBindVertexArray(sprite.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}
};
