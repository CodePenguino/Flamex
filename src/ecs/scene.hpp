#pragma once

#include <entt/entt.hpp>

namespace ECS
{
	class Entity;

	class Scene
	{
	public:
		~Scene();

		inline void use();

		Entity create_entity();
		void destroy_entity(Entity& entity);

		template<typename... Components>
		auto get_all_entities_with()
		{
			return m_registry.view<Components...>();
		}

	private:
		entt::registry m_registry;
		friend class Entity;
	};

	static Scene* current_scene;

	inline void Scene::use()
	{
		current_scene = this;
	}
};
