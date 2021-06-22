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
		struct MeshComponent
		{

		};
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

			operator glm::mat4& ()      { return Transform; }
			operator const glm::mat4&() { return Transform; }
		};

		// se crea el registro
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		// creacion de un componente
		if (m_Registry.has<TransformComponent>(entity))
		TransformComponent& transform = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f)); // registro y argumento

		// mirar si un entity en concreto tiene un componente
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			// itera sobre todas las entidades en mi registro/scena que contegan el transforComponent
			TransformComponent& transform = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
		}

	//	auto group = m_Registry.group<MeshComponent>(entt::get<MeshComponent>);
	//	for (auto entity : group)
		{
			//auto& [ransform, mesh]  =  group.get<TransformComponent, MeshComponent>(entity);
		}
			



	
	}

	Scene::~Scene()
	{
	}


	
}