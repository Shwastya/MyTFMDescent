#include "../src/engine/mhpch.cpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/utils/Library.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Engine.hpp"

#define W_     static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H_    static_cast<float>(Engine::p().GetWindow().GetHeight())

#define SHADER_C    std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("PhongC"))
#define SHADER_T    std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("PhongT"))

#define CT_SINGLE   std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("simpleT"))




namespace MHelmet
{

	enum  Geometries { triangle = 0, quad, cube, sphere, teapot };

	struct RendererGeometryAssets
	{
		RefCount<VAO> VAO[5];
		ShaderLib SLib; // SHADER_C LIBRARY // La idea es textura o color

		RefCount<Texture2D> WhiteTextu;
	};
	static Unique<RendererGeometryAssets> s_Data;

	static BUFFER::Layout GetLayout()
	{
		BUFFER::Layout layout = 
		{
			{BUFFER::DataType::Float3, "a_Pos"         },
			{BUFFER::DataType::Float2, "a_UVS"         },
			{BUFFER::DataType::Float3, "a_Normals"     },
			{BUFFER::DataType::Float3, "a_Tangents"    },
			{BUFFER::DataType::Float3, "a_BiTangents"  }
		};
		return layout;
	}

	static void setMaterialUniforms(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const int& shininess)
	{
		SHADER_C->Uniform("u_material.ambient", ambient);
		SHADER_C->Uniform("u_material.diffuse", diffuse);
		SHADER_C->Uniform("u_material.specular", specular);
		SHADER_C->Uniform("u_material.shininess", shininess); 
	}

	void RendererGeometry::Init() // Inicializacion statica (1 instancia)
	{
		// Instancia de los recursos para las 
		s_Data = std::make_unique<RendererGeometryAssets>();

		// Librerias de shaders
		s_Data->SLib.Load("PhongC", "../shaders/3D/COLOR/phong2.glsl");
		s_Data->SLib.Load("PhongT", "../shaders/3D/TEXTU/phong2.glsl");
		s_Data->SLib.Load("simpleT", "../shaders/texture2D.glsl");

		// testeando movidas

		s_Data->WhiteTextu = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTextu->SetData(&whiteTextureData, sizeof(uint32_t));
		
		/////////////// Triangle ///////////////
		{
			Triangle T;
			s_Data->VAO[triangle] = VAO::Create();

			RefCount<VBO> VBO_T = VBO::Create(T.Get(), T.SizeVBO());
			VBO_T->SetLayout(GetLayout());
			s_Data->VAO[triangle]->Add__VBO(VBO_T);

			RefCount<EBO> EBO_T = std::make_shared<OpenGLEBO>(T.Indices(), T.SizeIndices());

			s_Data->VAO[triangle]->Add__EBO(EBO_T);
		}		

		/////////////// Quad ///////////////
		{
			Quad Q(1.0f);
			s_Data->VAO[quad] = VAO::Create();

			RefCount<VBO> VBO_Q = VBO::Create(Q.Get(), Q.SizeVBO());
			VBO_Q->SetLayout(GetLayout());
			s_Data->VAO[quad]->Add__VBO(VBO_Q);

			RefCount<EBO> EBO_Q = std::make_shared<OpenGLEBO>(Q.Indices(), Q.SizeIndices());
			s_Data->VAO[quad]->Add__EBO(EBO_Q);
		}

		/////////////// Cube ///////////////
		{
			Cube C(1.0f);
			s_Data->VAO[cube] = VAO::Create();

			RefCount<VBO> VBO_C = VBO::Create(C.Get(), C.SizeVBO());
			VBO_C->SetLayout(GetLayout());
			s_Data->VAO[cube]->Add__VBO(VBO_C);

			RefCount<EBO> EBO_C = std::make_shared<OpenGLEBO>(C.Indices(), C.SizeIndices());
			s_Data->VAO[cube]->Add__EBO(EBO_C);
		}
		

		/////////////// Sphere ///////////////
		{
			Sphere S(1.0f, 50, 50);
			s_Data->VAO[sphere] = VAO::Create();

			RefCount<VBO> VBO_S = VBO::Create(S.Get(), S.SizeVBO());
			VBO_S->SetLayout(GetLayout());
			s_Data->VAO[sphere]->Add__VBO(VBO_S);

			RefCount<EBO> EBO_S = std::make_shared<OpenGLEBO>(S.Indices(), S.SizeIndices());
			s_Data->VAO[sphere]->Add__EBO(EBO_S);
		}
		

		/////////////// Teapot ///////////////
		{
			Teapot TP(50);
			s_Data->VAO[teapot] = VAO::Create();

			RefCount<VBO> VBO_TP = VBO::Create(TP.Get(), TP.SizeVBO());
			VBO_TP->SetLayout(GetLayout());
			s_Data->VAO[teapot]->Add__VBO(VBO_TP);

			RefCount<EBO> EBO_TP = std::make_shared<OpenGLEBO>(TP.Indices(), TP.SizeIndices());
			s_Data->VAO[teapot]->Add__EBO(EBO_TP);
		}
				
	}

	void RendererGeometry::ShutDown()
	{
		//delete s_Data;
	}

	void RendererGeometry::BeginScene(const PerspectiveCamera& camera, const glm::vec3& LightPos, const glm::vec2& viewport)
	{
		SHADER_C->Bind();

		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();		

		SHADER_C->Uniform("u_view", view);
		
		SHADER_C->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), viewport.x / viewport.y, 0.1f, 100.0f));
		// SHADER_C->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_ / H_, 0.1f, 100.0f));
	
		SHADER_C->Uniform("u_viewPos", camera.GetPosition());

		// LIGHT
		SHADER_C->Uniform("u_light.position", LightPos);
		SHADER_C->Uniform("u_light.ambient", 0.8f, 0.1f, 0.1f);
		SHADER_C->Uniform("u_light.diffuse", 0.5f, 0.5f, 0.5f);
		SHADER_C->Uniform("u_light.specular", 1.0f, 1.0f, 1.0f);
	}

	void RendererGeometry::EndScene()
	{
		SHADER_C->Unbind();
		SHADER_T->Unbind();
		CT_SINGLE->Unbind();
	}

	void RendererGeometry::DrawTriangle(const glm::vec3 position, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		glm::mat4 T_model = glm::mat4(1.0f);		 

		T_model = glm::translate(T_model, position);
		T_model = glm::rotate(T_model, degrees, rotate);
		T_model = glm::scale(T_model, size);

		// ambient  // diffuse  // specular // sininess  
		setMaterialUniforms({ 0.7f, 0.5f, 0.4f }, { 0.7f, 0.5f, 0.4f }, { 0.5f, 0.5f, 0.5f }, 32);

		SHADER_C->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(T_model))));
		SHADER_C->Uniform("u_model", T_model);
		  
		s_Data->VAO[triangle]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[triangle]);
	}

	void RendererGeometry::DrawQuad(const glm::vec3 position, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		glm::mat4 Q_model = glm::mat4(1.0f);

		Q_model = glm::translate(Q_model, position);
		Q_model = glm::rotate(Q_model, degrees, rotate);
		Q_model = glm::scale(Q_model, size);


		// ambient  // diffuse  // specular // sininess  
		setMaterialUniforms({ 0.7f, 0.5f, 0.4f }, { 0.7f, 0.5f, 0.4f }, { 0.5f, 0.5f, 0.5f }, 32);

		SHADER_C->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(Q_model))));
		SHADER_C->Uniform("u_model", Q_model);

		s_Data->VAO[quad]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[quad]);
	}	

	void RendererGeometry::DrawCube(const glm::vec3 position, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{
		
		glm::mat4 C_model = glm::mat4(1.0f);

		C_model = glm::translate(C_model, position);
		C_model = glm::rotate(C_model, degrees, rotate);
		C_model = glm::scale(C_model, size);

		// ambient  // diffuse  // specular // sininess  
		setMaterialUniforms({ 0.7f, 0.5f, 0.4f }, { 0.7f, 0.5f, 0.4f }, { 0.5f, 0.5f, 0.5f }, 32);

		SHADER_C->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(C_model))));
		SHADER_C->Uniform("u_model", C_model);

		s_Data->VAO[cube]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[cube]);
	}

	void RendererGeometry::DrawSphere(const glm::vec3 position, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{		
		glm::mat4 S_model = glm::mat4(1.0f);

		S_model = glm::translate(S_model, position);
		S_model = glm::rotate(S_model, degrees, rotate);
		S_model = glm::scale(S_model, size);

		// ambient  // diffuse  // specular // sininess  
		setMaterialUniforms({0.7f, 0.5f, 0.4f}, {0.7f, 0.5f, 0.4f}, {0.5f, 0.5f, 0.5f}, 32);
		
		SHADER_C->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(S_model))));
		SHADER_C->Uniform("u_model", S_model);		

		s_Data->VAO[sphere]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[sphere]);
	}

	void RendererGeometry::DrawTeapot(const glm::vec3 position, const glm::vec3& size, const glm::vec3& rotate, const float& degrees)
	{		
		glm::mat4 TP_model = glm::mat4(1.0f);

		TP_model = glm::translate(TP_model, position);
		TP_model = glm::rotate(TP_model, degrees, rotate);
		TP_model = glm::scale(TP_model, size);

		// ambient  // diffuse  // specular // sininess  
		setMaterialUniforms({ 0.7f, 0.5f, 0.4f }, { 0.7f, 0.5f, 0.4f }, { 0.5f, 0.5f, 0.5f }, 32);

		SHADER_C->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(TP_model))));
		SHADER_C->Uniform("u_model", TP_model);

		s_Data->VAO[teapot]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[teapot]);
	}

























	/* SIMPLE QUAD Texture */

	void RendererGeometry::DrawSimpleTextureQuad(const PerspectiveCamera& camera, const RefCount<Texture2D>& texture, const glm::vec3& position, const glm::vec3& size)
	{
		CT_SINGLE->Bind();


		// Color or texture
		CT_SINGLE->Uniform("u_color", glm::vec4(1.0f));
		texture->Bind(0);
		CT_SINGLE->Uniform("u_text", 0);


		// model transformations and movidas
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		model = glm::translate(model, position);

		CT_SINGLE->Uniform("u_view", view);
		CT_SINGLE->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));
		CT_SINGLE->Uniform("u_model", model);
		// VAO BIND
		s_Data->VAO[quad]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[quad]);
	}

	/* SIMPLE QUAD color */

	void RendererGeometry::DrawSimpleColorQuad(const PerspectiveCamera& camera, const glm::vec4& color, const glm::vec3& position)
	{
		CT_SINGLE->Bind();

		// Color or texture
		CT_SINGLE->Uniform("u_color", color);
		s_Data->WhiteTextu->Bind(0);


		// Model transformations
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);

		CT_SINGLE->Uniform("u_view", view);
		CT_SINGLE->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));
		CT_SINGLE->Uniform("u_model", model);
		// VAO BIND
		s_Data->VAO[quad]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[quad]);
	}

}