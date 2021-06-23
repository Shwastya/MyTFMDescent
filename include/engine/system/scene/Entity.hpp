#pragma once
#include "engine/system/scene/Scene.hpp"
#include "entt.hpp"
#include "engine/system/MHCore.hpp"

namespace MHelmet
{
	// entity tendra una referencia a escena
	class Entity
	{


	public:
		Entity() = default;
		Entity(entt::entity wrap, Scene* scene);
		Entity(const Entity& other) = default;

		~Entity() { /*delete m_Scene; */ }

		//void WrapScene(Scene* scene) { m_Scene = scene; }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				CORE_ERROR("Entity already has component!");
				//break;
			}
			return m_Scene->m_Registry.emplace<T>(m_EntityWrap, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>())
			{
				CORE_ERROR("Not have component!");
				//break;
			}
			

			return m_Scene->m_Registry.get<T>(m_EntityWrap);
		}

		template<typename T>
		bool HasComponent()	
		{ 
			return m_Scene->m_Registry.has<T>(m_EntityWrap);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				CORE_WARN("Not have component to remove!");
				//break;
			}
			m_Scene->m_Registry.remove<T>>(m_EntityWrap);
		}
		operator bool() const { return m_EntityWrap != entt::null; }

		// para que la clase hierarchy pueda recoger el entitywarp como uint32_t
		operator uint32_t() const { return static_cast<uint32_t>(m_EntityWrap); }
	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityWrap{ entt::null };
		
	};
}