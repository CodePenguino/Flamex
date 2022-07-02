#pragma once

#include "scene.hpp"
#include "components.hpp"
#include <iostream>

#include <entt/entt.hpp>

namespace ECS
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene) : m_handle(handle), m_scene(scene) {}
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& add_component(Args&&... args)
		{
			if(has_component<T>()) {
				std::cerr << "Error: Entity ' "<< (uint32_t)m_handle << "' already has component!\n";
			}

			T& component = m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& add_or_replace_component(Args&&... args)
		{
			T& component = m_scene->m_registry.emplace_or_replace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& get_component()
		{
			if(!has_component<T>()) {
				std::cerr << "Error: Entity ' "<< (uint32_t)m_handle << "' does not have component!\n";
			}

			return m_scene->m_registry.get<T>(m_handle);
		}

		template<typename T>
		inline bool has_component()
		{
			return m_scene->m_registry.all_of<T>(m_handle);
		}

		template<typename T>
		void remove_component()
		{
			if(!has_component<T>()) {
				std::cerr << "Error: Entity ' "<< (uint32_t)m_handle << "' does not have component!\n";
			}

			m_scene->m_registry.remove<T>(m_handle);
		}

		operator bool() const { return m_handle != entt::null; }
		operator entt::entity() const { return m_handle; }
		operator uint32_t() const { return (uint32_t)m_handle; }

		inline bool operator==(const Entity& other) const
		{
			return m_handle == other.m_handle && m_scene == other.m_scene;
		}

		inline bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		//  ----------------------------------------------------------
		// |               Type initialization functions              |
		//  ----------------------------------------------------------

		void init_sprite(const char* file_path, float resolution = 360)
		{
			*this = current_scene->create_entity();

			add_component<Transform3DComponent>();
			add_component<SpriteComponent>(file_path, resolution);
		}

		void init_camera_ortho(const glm::vec3& pos, float zNear = 0.03f, float zFar = 100.0f)
		{
			*this = current_scene->create_entity();

			add_component<CameraComponent>();
			get_component<CameraComponent>().init_ortho(pos, zNear, zFar);
		}

		void init_camera_perspective(const glm::vec3& pos, float fov = 70.0f, float zNear = 0.03f, float zFar = 100.0f)
		{
			*this = current_scene->create_entity();

			add_component<CameraComponent>();
			get_component<CameraComponent>().init_perspective(pos, fov, zNear, zFar);
		}

	private:
		entt::entity m_handle { entt::null };
		Scene* m_scene = nullptr;
	};

}
