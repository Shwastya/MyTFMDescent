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
		//static void ShutDown();

		static void BeginScene(const CameraFirstPerson& camera);
		static void EndScene();

		static void DrawDirectionalLight(const LightComponent& light);
		static void DrawPointLights(const PointLightComponent& PL, const glm::vec3& position, const uint32_t idx = 0);
		static void DrawSpotLights(const SpotLightComponent& SL, const glm::vec3& position, const glm::vec3& direction, const uint32_t idx = 0);

		//static void DrawSpotLights(const PointLightComponent& PL);

		static void DrawTriangle(const glm::mat4& transform, const MaterialComponent& material);
		static void DrawTriangle(const glm::mat4& transform, const TextureComponent& texture);

		static void DrawQuad(const glm::mat4& transform, const MaterialComponent& material);
		static void DrawQuad(const glm::mat4& transform, const TextureComponent& texture);	

		static void DrawCube(const glm::mat4& transform, const MaterialComponent& material, bool rotate = false);
		static void DrawCube(const glm::mat4& transform, const TextureComponent& texture , bool rotate = false);

		

		static void DrawSphere(const glm::mat4& transform, const MaterialComponent& material);
		static void DrawSphere(const glm::mat4& transform, const TextureComponent& texture);
		
		static void DrawTeapot(const glm::mat4& transform, const MaterialComponent& material);
		static void DrawTeapot(const glm::mat4& transform, const TextureComponent& texture);
	public:
	};
}