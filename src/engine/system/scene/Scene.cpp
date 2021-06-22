#include "engine/system/scene/Scene.hpp"
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>


namespace MHelmet
{
	static void DoMath(const glm::mat4& transform)
	{

	}

	Scene::Scene()
	{
		// componentes sin ningun tipo de polimorfismo
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

		};


		Scene::Scene()
		{
			// entity basicamente es solo un tipo uint32_t
			entt::entity entity = m_Registry.create();

			m_Registry.emplace<>();
		}

		Scene::~Scene()
		{

		}
	}
	
}