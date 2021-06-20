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

		ShaderLib SLib; // SHADER LIBRARY // La idea es textura o color
	};

	static Unique<RendererGeometryAssets> s_Data;

	void RendererGeometry::Init()
	{
		// Instancia de los recursos para las 
		s_Data = std::make_unique<RendererGeometryAssets>();

		// Librerias de shaders
		s_Data->SLib.Load("PhongC", "../shaders/3D/COLOR/phong1.glsl");

		// TODAS LAS GEOMETRIAS
		// Triangle
		Triangle T;

		s_Data->VAO[triangle] = VAO::Create();

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

		// Quad
		Quad Q(1.0f);

		s_Data->VAO[quad] = VAO::Create();

		RefCount<VBO> VBO_Q;
		VBO_Q = VBO::Create(Q.Get(), Q.SizeVBO());

		VBO_Q->SetLayout
		({
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
		});

		s_Data->VAO[quad]->Add__VBO(VBO_Q);

		RefCount<EBO> EBO_Q;
		EBO_Q = std::make_shared<OpenGLEBO>(Q.Indices(), Q.SizeIndices());

		s_Data->VAO[quad]->Add__EBO(EBO_Q);

		// Cube
		Cube C(1.0f);

		s_Data->VAO[cube] = VAO::Create();

		RefCount<VBO> VBO_C;
		VBO_C = VBO::Create(C.Get(), C.SizeVBO());

		VBO_C->SetLayout
		({
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
		});

		s_Data->VAO[cube]->Add__VBO(VBO_C);

		RefCount<EBO> EBO_C;
		EBO_C= std::make_shared<OpenGLEBO>(C.Indices(), C.SizeIndices());

		s_Data->VAO[cube]->Add__EBO(EBO_C);

		// Sphere
		Sphere S(1.0f, 50, 50);

		s_Data->VAO[sphere] = VAO::Create();

		RefCount<VBO> VBO_S;
		VBO_S = VBO::Create(S.Get(), S.SizeVBO());

		VBO_S->SetLayout
		({
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
		});

		s_Data->VAO[sphere]->Add__VBO(VBO_S);

		RefCount<EBO> EBO_S;
		EBO_S = std::make_shared<OpenGLEBO>(S.Indices(), S.SizeIndices());

		s_Data->VAO[sphere]->Add__EBO(EBO_S);

		// Teapot
		Teapot TP(50);

		s_Data->VAO[teapot] = VAO::Create();

		RefCount<VBO> VBO_TP;
		VBO_TP = VBO::Create(TP.Get(), TP.SizeVBO());

		VBO_TP->SetLayout
		({
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
			});

		s_Data->VAO[teapot]->Add__VBO(VBO_TP);

		RefCount<EBO> EBO_TP;
		EBO_TP = std::make_shared<OpenGLEBO>(TP.Indices(), TP.SizeIndices());

		s_Data->VAO[teapot]->Add__EBO(EBO_TP);

		
	}

	void RendererGeometry::ShutDown()
	{
		//delete s_Data;
	}

	void RendererGeometry::BeginScene(const PerspectiveCamera& camera, const glm::vec3& LightPos, const glm::vec3& LightColor, const int& Shininess, const float& ambientStrg, const float& SpecularStrg)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Bind();

		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();		

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_view", view);
		
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_lightColor", LightColor);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_lightPos", LightPos);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_shininess", Shininess);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_ambientStrength", ambientStrg);
		
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_specularStrength", SpecularStrg);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_viewPos", camera.GetPosition());


	}

	void RendererGeometry::EndScene()
	{
	}

	void RendererGeometry::DrawTriangle(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_objectColor", color);

		glm::mat4 T_model = glm::mat4(1.0f);		 

		T_model = glm::translate(T_model, position);
		T_model = glm::rotate(T_model, degrees, rotate);
		T_model = glm::scale(T_model, size);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(T_model))));
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_model", T_model);
		  
		s_Data->VAO[triangle]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[triangle]);
	}

	void RendererGeometry::DrawQuad(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_objectColor", color);

		glm::mat4 Q_model = glm::mat4(1.0f);

		Q_model = glm::translate(Q_model, position);
		Q_model = glm::rotate(Q_model, degrees, rotate);
		Q_model = glm::scale(Q_model, size);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(Q_model))));
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_model", Q_model);

		s_Data->VAO[quad]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[quad]);
	}

	void RendererGeometry::DrawCube(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_objectColor", color);

		glm::mat4 C_model = glm::mat4(1.0f);

		C_model = glm::translate(C_model, position);
		C_model = glm::rotate(C_model, degrees, rotate);
		C_model = glm::scale(C_model, size);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(C_model))));
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_model", C_model);

		s_Data->VAO[cube]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[cube]);
	}

	void RendererGeometry::DrawSphere(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_objectColor", color);

		glm::mat4 S_model = glm::mat4(1.0f);

		S_model = glm::translate(S_model, position);
		S_model = glm::rotate(S_model, degrees, rotate);
		S_model = glm::scale(S_model, size);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(S_model))));
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_model", S_model);		

		s_Data->VAO[sphere]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[sphere]);
	}

	void RendererGeometry::DrawTeapot(const glm::vec3 position, const glm::vec3& color, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_objectColor", color);

		glm::mat4 TP_model = glm::mat4(1.0f);

		TP_model = glm::translate(TP_model, position);
		TP_model = glm::rotate(TP_model, degrees, rotate);
		TP_model = glm::scale(TP_model, size);

		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(TP_model))));
		SHADER(s_Data->SLib.Get("PhongC"))->Uniform("u_model", TP_model);

		s_Data->VAO[teapot]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[teapot]);
	}

}