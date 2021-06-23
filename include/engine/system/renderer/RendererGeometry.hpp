#pragma once

#include "engine/system/geometry/triangle.hpp"
#include "engine/system/geometry/quad.hpp"
#include "engine/system/geometry/cube.hpp"
#include "engine/system/geometry/sphere.hpp"
#include "engine/system/geometry/teapot.hpp"
#include "PerspectiveCamera.hpp"
#include "engine/system/scene/Components.hpp"




namespace MHelmet
{
	struct Texture2D;

	class RendererGeometry
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const CameraManComponent& camera, const LightComponent& light);
		static void BeginScene(const PerspectiveCamera& camera, const glm::vec3& LightPos, const glm::vec2& viewport); // pasar struct de Light
		static void EndScene();

		// primitives
		static void DrawTriangle(const glm::vec3 position, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);

		static void DrawQuad(const glm::vec3 position,  const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);

	

		static void DrawCube(const glm::vec3 position,  const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);

		static void DrawSphere(const glm::vec3 position,  const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);
		
		static void DrawTeapot(const TransformComponent& transform, const MaterialComponent& material);
















		static void DrawSimpleTextureQuad(const PerspectiveCamera& camera, const RefCount<Texture2D>& texture, const glm::vec3& position = glm::vec3{ 0.0f }, const glm::vec3& size = glm::vec3{ 1.0f });


		static void DrawSimpleColorQuad(const PerspectiveCamera& camera, const glm::vec4& color, const glm::vec3& position = glm::vec3{ 0.0f });

	public:
	};
}