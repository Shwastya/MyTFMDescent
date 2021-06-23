#pragma once
#include "engine/system/scene/Scene.hpp"
#include "entt.hpp"

namespace MHelmet
{
	// entity tendra una referencia a escena
	class Entity
	{


	public:
		Entity(entt::entity manager, RefCount<Scene> scene);

		template<typename T>
		bool HasComponent()
		{
			m_Scene->m_Registry.has<T>(m_EntityManager);
		}

	private:
		entt::entity m_EntityManager;
		RefCount<Scene> m_Scene;
	};
}