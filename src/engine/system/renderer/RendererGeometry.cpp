#include "../src/engine/mhpch.cpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/utils/Library.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Engine.hpp"
#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>
#define W_WIDTH  static_cast<float>(Engine::p().GetWindow().GetWidth())
#define W_HEIGHT static_cast<float>(Engine::p().GetWindow().GetHeight())


namespace MHelmet
{
	enum  Geometries { triangle = 0, quad, cube, sphere, teapot  };

	struct RendererGeometryAssets
	{
		RefCount<VAO> VAO[5];

		RefCount<ShaderLib> SLib; // SHADER LIBRARY // La idea es textura o color

		glm::mat4 Triangle;
		glm::mat4 Quad;
		glm::mat4 Cube;
		glm::mat4 Sphere;
		glm::mat4 TeaPot;
	};

	static RendererGeometryAssets* s_Data;

	void RendererGeometry::Init()
	{
		// Instancia de los recursos para las 
		s_Data = new RendererGeometryAssets();

		// Librerias de shaders
		s_Data->SLib->Load("PhongC", "../shaders/3D/COLOR/phong1.glsl");

		// TODAS LAS GEOMETRIAS

		// Triangle
		Triangle T;

		s_Data->VAO[triangle].reset(VAO::Create());

		RefCount<VBO> VBO_T;
		VBO_T = VBO::Create(T.Get(), T.SizeVBO());

		VBO_T->SetLayout
		({
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
		});

		s_Data->VAO[triangle]->Add__VBO(VBO_T);

		RefCount<EBO> EBO_T;
		EBO_T = std::make_shared<OpenGLEBO>(T.Indices(), T.SizeIndices());

		s_Data->VAO[triangle]->Add__EBO(EBO_T);

		
	}

	void RendererGeometry::ShutDown()
	{
		delete s_Data;
	}

	void RendererGeometry::BeginScene(const PerspectiveCamera& camera, const glm::vec3& LightPos, const glm::vec3& LightColor, const int& Shininess, const float& ambientStrg, const float& SpecularStrg)
	{
		SHADER(s_Data->SLib->Get("PhongC"))->Bind();

		View = glm::mat4(1.0f);
		View = camera.GetViewMatrix();		

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_view", camera.GetViewMatrix());
		
		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_lightColor", LightColor);

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_lightPos", LightPos);

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_shininess", Shininess);

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_ambientStrength", ambientStrg);
		
		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_specularStrength", SpecularStrg);

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_viewPos", camera.GetPosition());	
	}

	void RendererGeometry::EndScene()
	{
	}

	void RendererGeometry::DrawTriangle(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
		SHADER(s_Data->SLib->Get("PhongC"))->Bind();

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_objectColor", color);

		s_Data->Triangle = glm::mat4(1.0f);			 

		s_Data->Triangle = glm::translate(s_Data->Triangle, position);

		SHADER(s_Data->SLib->Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(s_Data->Triangle))));
	}

	void RendererGeometry::DrawQuad(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
	}

	void RendererGeometry::DrawCube(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
	}

	void RendererGeometry::DrawSphere(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
	}

	void RendererGeometry::DrawTeapot(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
	}

}