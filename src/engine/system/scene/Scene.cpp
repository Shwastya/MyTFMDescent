#include "engine/system/scene/Scene.hpp"
#include "../src/engine/mhpch.cpp"
#include "engine/system/scene/Components.hpp"
#include "engine/system/renderer/RendererGeometry.hpp"


namespace MHelmet
{
	static void DoMath(const glm::mat4& transform)
	{

	}

	Scene::Scene()
	{
		// componentes sin ningun tipo de polimorfismo
		

		// se crea el registro
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

	//	m_Registry.on_construct<TransformComponent>().connect<&ontransform>();

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

		
			



	
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::Update(DeltaTime dt)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<MaterialComponent>);
		for (auto entity : group)
		{
			auto& [transform, quad] = group.get<TransformComponent, MaterialComponent>(entity);
			
			//RendererGeometry::DrawSimpleColorQuad(transform, quad.Material);
		}
	}


	
}