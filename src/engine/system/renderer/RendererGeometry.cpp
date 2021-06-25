#include "../src/engine/mhpch.cpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/utils/Library.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Engine.hpp"

#define W_ static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H_ static_cast<float>(Engine::p().GetWindow().GetHeight())

#define SHADER std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("PhongT"))




namespace MHelmet
{

	enum  Geometries { triangle = 0, quad, cube, sphere, teapot };

	struct RendererGeometryAssets
	{
		RefCount<VAO> VAO[5];
		ShaderLib SLib; // SHADER LIBRARY // La idea es textura o color

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

	static void SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const int& shininess)
	{
		
		SHADER->Uniform("u_IsMaterial", 1);
		SHADER->Uniform("u_material.ambient", ambient);
		SHADER->Uniform("u_material.diffuse", diffuse);
		SHADER->Uniform("u_material.specular", specular);
		SHADER->Uniform("u_material.shininess", shininess); 
	}
	static void SetTexture(const Texture2D& albedo, const Texture2D& specular)
	{
			SHADER->Uniform("u_IsMaterial", 0);
			albedo.Bind(0);
			SHADER->Uniform("u_matTexture.diffuse", 0);
			specular.Bind(1);
			SHADER->Uniform("u_matTexture.specular", 1);
	}

	static void SettLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
	{
		SHADER->Uniform("u_light.direction", direction);
		SHADER->Uniform("u_light.ambient", ambient);
		SHADER->Uniform("u_light.diffuse", diffuse);
		SHADER->Uniform("u_light.specular", specular);
	}
	static void SubmitModelToScene(const glm::mat4& model, const Geometries& vao)
	{
		SHADER->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(model))));
		SHADER->Uniform("u_model", model);

		s_Data->VAO[vao]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[vao]);
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

	void RendererGeometry::EndScene() { SHADER->Unbind(); }
//	void RendererGeometry::ShutDown() {}

	void RendererGeometry::BeginScene(const CameraManComponent& C, const LightComponent& L)
	{

		SHADER->Bind();
		glm::mat4 view = glm::mat4(1.0f);
		view = C.Cameraman.Get().GetViewMatrix();		
		SHADER->Uniform("u_view", view);		
		SHADER->Uniform("u_proj", glm::perspective
		(
			glm::radians
			(
				C.Cameraman.Get().GetFOV()),
				C.ViewportX / C.ViewportY,
				C.Near, C.Far
			)
		);	
		SHADER->Uniform("u_viewPos", C.Cameraman.Get().GetPosition());
		SettLight(L.Direction, L.Ambient, L.Difusse, L.Specular);		
	}

	

	// TRIANGLES
	void RendererGeometry::DrawTriangle(const glm::mat4& trans, const MaterialComponent& m)
	{
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, triangle);
	}

	void RendererGeometry::DrawTriangle(const glm::mat4& trans, const TextureComponent& texture)
	{
		glm::mat4 model = trans;
		SetTexture(*texture.Albedo, *texture.Specular);
		SubmitModelToScene(model, triangle);
	}


	// QUADS
	void RendererGeometry::DrawQuad(const glm::mat4& trans, const MaterialComponent& m)
	{
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, quad);
	}
	void RendererGeometry::DrawQuad(const glm::mat4& trans, const TextureComponent& texture)
	{
		glm::mat4 model = trans;
		SetTexture(*texture.Albedo, *texture.Specular);
		SubmitModelToScene(model, quad);
	}



	// CUBES
	void RendererGeometry::DrawCube(const glm::mat4& trans, const MaterialComponent& m)
	{
		
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, cube);
	}
	void RendererGeometry::DrawCube(const glm::mat4& trans, const TextureComponent& texture)
	{
		glm::mat4 model = trans;		
		SetTexture(*texture.Albedo, *texture.Specular);
		SubmitModelToScene(model, cube);
	}


    // SPHERES
	void RendererGeometry::DrawSphere(const glm::mat4& trans, const MaterialComponent& m)
	{		
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, sphere);
	}
	void RendererGeometry::DrawSphere(const glm::mat4& trans, const TextureComponent& texture)
	{
		glm::mat4 model = trans;
		SetTexture(*texture.Albedo, *texture.Specular);
		SubmitModelToScene(model, sphere);
	}



	// TEAPOTS
	void RendererGeometry::DrawTeapot(const glm::mat4& trans, const MaterialComponent& m)
	{
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, teapot);
	}

	void RendererGeometry::DrawTeapot(const glm::mat4& trans, const TextureComponent& texture)
	{
		glm::mat4 model = trans;
		SetTexture(*texture.Albedo, *texture.Specular);
		SubmitModelToScene(model, teapot);
	}


	

























	/* SIMPLE QUAD Texture */

	//void RendererGeometry::DrawSimpleTextureQuad(const PerspectiveCamera& camera, const RefCount<Texture2D>& texture, const glm::vec3& position, const glm::vec3& size)
	//{
	//	CT_SINGLE->Bind();


	//	// Color or texture
	//	CT_SINGLE->Uniform("u_color", glm::vec4(1.0f));
	//	texture->Bind(0);
	//	CT_SINGLE->Uniform("u_text", 0);


	//	// model transformations and movidas
	//	glm::mat4 view = glm::mat4(1.0f);
	//	view = camera.GetViewMatrix();
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::scale(model, size);
	//	model = glm::translate(model, position);

	//	CT_SINGLE->Uniform("u_view", view);
	//	CT_SINGLE->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));
	//	CT_SINGLE->Uniform("u_model", model);
	//	// VAO BIND
	//	s_Data->VAO[quad]->Bind();
	//	RenderDrawCall::Draw(s_Data->VAO[quad]);
	//}

	///* SIMPLE QUAD color */

	//void RendererGeometry::DrawSimpleColorQuad(const PerspectiveCamera& camera, const glm::vec4& color, const glm::vec3& position)
	//{
	//	CT_SINGLE->Bind();

	//	// Color or texture
	//	CT_SINGLE->Uniform("u_color", color);
	//	s_Data->WhiteTextu->Bind(0);


	//	// Model transformations
	//	glm::mat4 view = glm::mat4(1.0f);
	//	view = camera.GetViewMatrix();
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, position);

	//	CT_SINGLE->Uniform("u_view", view);
	//	CT_SINGLE->Uniform("u_proj", glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT, 0.1f, 100.0f));
	//	CT_SINGLE->Uniform("u_model", model);
	//	// VAO BIND
	//	s_Data->VAO[quad]->Bind();
	//	RenderDrawCall::Draw(s_Data->VAO[quad]);
	//}

}