#pragma once

#include "engine/system/geometry/triangle.hpp"
#include "engine/system/geometry/quad.hpp"
#include "engine/system/geometry/cube.hpp"
#include "engine/system/geometry/sphere.hpp"
#include "engine/system/geometry/teapot.hpp"
#include "PerspectiveCamera.hpp"




namespace MHelmet
{
	class RendererGeometry
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const PerspectiveCamera& camera, const glm::vec3& LightPos, const glm::vec3& LightColor, const int& Shininess = 32, const float& ambient = 0.2f, const float& SpecularStrg = 0.7f);
		static void EndScene();

		// primitives
		static void DrawTriangle(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);
		static void DrawQuad(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);
		static void DrawCube(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);
		static void DrawSphere(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);
		static void DrawTeapot(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size = glm::vec3{ 1.0f }, const glm::vec3& rotate = glm::vec3{ 1.0f }, const float& degrees = 0.0f);

	public:
	};
}