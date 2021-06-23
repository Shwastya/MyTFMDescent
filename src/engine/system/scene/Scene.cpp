#include "engine/system/scene/Scene.hpp"
#include "../src/engine/mhpch.cpp"
#include "engine/system/scene/Components.hpp"
#include "engine/system/renderer/RendererGeometry.hpp"


namespace MHelmet
{
	// ejemplos
	static void OnTransformConstruct() // on construct conectamos con esta funcion
	{

	}


	Scene::Scene()
	{		
		// componentes sin ningun tipo de polimorfismo
		/*struct MeshComponent
		{
			bool Mesh;
			MeshComponent() = default;
		};*/
		//struct TransformComponent
		//{
		//	glm::mat4 Transform;

		//	TransformComponent() = default;
		//	TransformComponent(const TransformComponent&) = default;
		//	TransformComponent(const glm::mat4& transform)
		//		: Transform(transform) {}

		//	operator glm::mat4& ()      { return Transform; }
		//	operator const glm::mat4&() { return Transform; }
		//};

		//// se crea el registro
		//entt::entity entity = m_Registry.create();
		//m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		// on construct podemos conectar con una funcion (tipo puntero a funcion)
		//m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>(); // puntero a funcion statica


		// creacion de un componente
		//if (m_Registry.has<TransformComponent>(entity))
		//	TransformComponent& transform = m_Registry.emplace<TransformComponent>(entity); // registro y argumento


		// mirar si un entity en concreto tiene un componente
		//auto view = m_Registry.view<TransformComponent>();
		//for (auto entity : view)
		//{
		//	// itera sobre todas las entidades en mi registro/scena que contegan el transforComponent
		//	TransformComponent& transform = view.get<TransformComponent>(entity);
		//}

		//auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		//for (auto entity : group)
		//{
		//	// itera sobre todas las entidades en mi registro/scena que contegan el transforComponent
		//	auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		//}



		
			



	
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
			auto& [transform, material] = group.get<TransformComponent, MaterialComponent>(entity);
		
			RendererGeometry::DrawTeapot(transform, material);
		
		}
	}


	
}