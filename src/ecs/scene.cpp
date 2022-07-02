#include "scene.hpp"
#include "entity.hpp"

namespace ECS
{
	// TODO: Delete all entities
	Scene::~Scene()
	{
	}

	Entity Scene::create_entity()
	{
		return { m_registry.create(), this };
	}

	void Scene::destroy_entity(Entity& entity)
	{
		m_registry.destroy(entity);
	}
}
