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
		static void EndScene();

		// primitives
		static void DrawTriangle(const glm::mat4& transform, const MaterialComponent& material);

		static void DrawQuad(const glm::mat4& transform, const MaterialComponent& material);

	

		static void DrawCube(const glm::mat4& transform, const MaterialComponent& material);

		static void DrawSphere(const glm::mat4& transform, const MaterialComponent& material);
		
		static void DrawTeapot(const glm::mat4& transform, const MaterialComponent& material);
















		static void DrawSimpleTextureQuad(const PerspectiveCamera& camera, const RefCount<Texture2D>& texture, const glm::vec3& position = glm::vec3{ 0.0f }, const glm::vec3& size = glm::vec3{ 1.0f });


		static void DrawSimpleColorQuad(const PerspectiveCamera& camera, const glm::vec4& color, const glm::vec3& position = glm::vec3{ 0.0f });

	public:
	};
}