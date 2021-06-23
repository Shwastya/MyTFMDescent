#include "../src/engine/mhpch.cpp"
#include "engine/system/scene/Entity.hpp"

namespace MHelmet
{
	Entity::Entity(entt::entity manager, RefCount<Scene> scene)
		: m_EntityManager(manager), m_Scene(scene)
	{
	}
}