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
		static void DrawTriangle(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color);
		static void DrawCube(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color);
		static void DrawSphere(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color);
		static void DrawTeapot(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color);

	public:
		
			// Model || View || Projection
			static glm::mat4 Projection;
			static glm::mat4 Model;
			static glm::mat4 View;
			// --------------------------			

			// SCENE BASIC PHONG TEMPORAL

			glm::vec3 LightColor = glm::vec3{ 1.0f, 1.0f, 1.0f };
			glm::vec3 LightPos = glm::vec3{ 3.0f, 4.0f, 3.0f };

			float AmbientStrength = 0.2f;
			float SpecularStrength = 0.7f;

			int Shininess = 32;

			glm::vec3 ViewPos; // desde la camara
		
	
	};
}