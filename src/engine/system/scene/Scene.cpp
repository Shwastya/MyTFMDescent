#include "engine/system/scene/Scene.hpp"
#include "../src/engine/mhpch.cpp"
#include "engine/system/scene/Components.hpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/scene/Entity.hpp"

namespace MHelmet
{
	// ejemplos
	//static void OnTransformConstruct() // on construct conectamos con esta funcion
	//{

	//}


	//Scene::Scene()
	//{		
	//	// componentes sin ningun tipo de polimorfismo
	//	/*struct MeshComponent
	//	{
	//		bool Mesh;
	//		MeshComponent() = default;
	//	};*/
	//	//struct TransformComponent
	//	//{
	//	//	glm::mat4 Transform;

	//	//	TransformComponent() = default;
	//	//	TransformComponent(const TransformComponent&) = default;
	//	//	TransformComponent(const glm::mat4& transform)
	//	//		: Transform(transform) {}

	//	//	operator glm::mat4& ()      { return Transform; }
	//	//	operator const glm::mat4&() { return Transform; }
	//	//};

	//	//// se crea el registro
	////	entt::entity entity = m_Registry.create();
	//	//m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

	//	// on construct podemos conectar con una funcion (tipo puntero a funcion)
	//	//m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>(); // puntero a funcion statica


	//	// creacion de un componente
	//	//if (m_Registry.has<TransformComponent>(entity))
	//	//	TransformComponent& transform = m_Registry.emplace<TransformComponent>(entity); // registro y argumento


	//	// mirar si un entity en concreto tiene un componente
	//	//auto view = m_Registry.view<TransformComponent>();
	//	//for (auto entity : view)
	//	//{
	//	//	// itera sobre todas las entidades en mi registro/scena que contegan el transforComponent
	//	//	TransformComponent& transform = view.get<TransformComponent>(entity);
	//	//}

	//	//auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
	//	//for (auto entity : group)
	//	//{
	//	//	// itera sobre todas las entidades en mi registro/scena que contegan el transforComponent
	//	//	auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
	//	//}



	//	
	//		



	//
	//}

	Scene::~Scene()
	{
	}



	Entity Scene::CreateEntity(const std::string& name)
	{		
		Entity e = { m_Registry.create(), this};
		//e.AddComponent<>
		e.AddComponent<TagComponent>(name);	
		return e;
	}
	
	
	void Scene::Update(DeltaTime dt)
	{		
		// BEGIN ESCENE
		{
			auto view_cameraman = m_Registry.view<CameraManComponent>();
			{
				for (auto C_entity : view_cameraman)
				{
					auto& cameraman = view_cameraman.get<CameraManComponent>(C_entity);

					if (cameraman.Primary)
					{
						if (cameraman.IsHovered) cameraman.Cameraman.Update(dt);

						auto view_light = m_Registry.view<LightComponent>();
						{
							for (auto L_entity : view_light)
							{
								auto& light = view_light.get<LightComponent>(L_entity);
								RendererGeometry::BeginScene(cameraman, light);
							}
						}
					}
				}
			}

			// geometries
			auto group = m_Registry.group<TransformComponent>(entt::get<MaterialComponent>);
			for (auto entity : group)
			{
				auto& [transform, material] = group.get<TransformComponent, MaterialComponent>(entity);

				RendererGeometry::DrawTeapot(transform.GetTransform(), material);
			}			
		}
		// END SCENE
		RendererGeometry::EndScene();
	}	
}