#include <MHpch.h>
#include "engine/system/scene/Entity.hpp"

namespace MHelmet
{
	Entity::Entity(entt::entity manager, Scene* scene)
		: m_EntityWrap(manager), m_Scene(scene)
	{
	//	m_Scene = std::make_shared<Scene>;
		//m_Scene = scene;
	}
	
}