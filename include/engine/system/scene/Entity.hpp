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
			}
			else
			return m_Scene->m_Registry.emplace<T>(m_EntityWrap, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>()) CORE_ERROR("Not have component!");			
			else
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
			}
			else
			m_Scene->m_Registry.remove<T>(m_EntityWrap);
		}
		operator bool() const { return m_EntityWrap != entt::null; }
	
		operator entt::entity() const { return m_EntityWrap; }
		operator uint32_t() const { return static_cast<uint32_t>(m_EntityWrap); }

		bool operator==(const Entity& other) const 
		{ 
			return m_EntityWrap == other.m_EntityWrap && m_Scene == other.m_Scene;
		}
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityWrap{ entt::null };		
	};
}