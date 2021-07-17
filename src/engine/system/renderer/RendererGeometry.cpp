#include <MHpch.h>
#include "engine/Engine.hpp"
#include "engine/system/geometry/triangle.hpp"
#include "engine/system/geometry/quad.hpp"
#include "engine/system/geometry/cube.hpp"
#include "engine/system/geometry/sphere.hpp"
#include "engine/system/geometry/teapot.hpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/scene/Components.hpp"
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/utils/Library.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/system/cameraManager/CameraFirstPerson.hpp"
#include "engine/system/renderer/Framebuffer.hpp"

#define W_ static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H_ static_cast<float>(Engine::p().GetWindow().GetHeight())

//#define SHADER std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("Vuelta"))

#define SHADER std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("PhongT"))
#define ScreenTexture std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("ScreenTexture"))


namespace MHelmet
{

	enum  Geometries { triangle = 0, quad, screen, cube, sphere, teapot };

	struct RendererGeometryAssets
	{
		RefCount<VAO> VAO[6];
		ShaderLib SLib; // SHADER LIBRARY // La idea es textura o color

		RefCount<Texture2D> WhiteTextu;
	};
	static Unique<RendererGeometryAssets> s_Data;

	static BUFFER::Layout GetLayout()
	{
		BUFFER::Layout layout = 
		{
			{BUFFER::DataType::Float3, "aPos"         },
			{BUFFER::DataType::Float2, "aUv"          },
			{BUFFER::DataType::Float3, "aNormal"      },
			{BUFFER::DataType::Float3, "aTangents"    },
			{BUFFER::DataType::Float3, "aBiTangents"  }
		};
		return layout;
	}

	static void SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const int& shininess)
	{
		
		SHADER->Uniform("u_IsMaterial", 1);
		SHADER->Uniform("materialM.ambient", ambient);
		SHADER->Uniform("materialM.diffuse", diffuse);
		SHADER->Uniform("materialM.specular", specular);
		SHADER->Uniform("materialM.shininess", shininess); 
	}
	static void SetTexture(const Texture2D& albedo, const Texture2D& specular, const Texture2D& normal, const int& shininn = 32)
	{
			SHADER->Uniform("u_IsMaterial", 0);

			albedo.Bind(0);
			SHADER->Uniform("material.diffuse", 0);

			specular.Bind(1);
			SHADER->Uniform("material.specular", 1);

			normal.Bind(2);
			SHADER->Uniform("material.normal", 2);

			SHADER->Uniform("material.shininess", shininn);
	}

	static void SetTextureQuadScreen()
	{

	}

	static void SettLight(const glm::vec3& direction, const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
	{
		SHADER->Uniform("dirLight.direction", direction);
		//SHADER->Uniform("dirLight.position", position);
		SHADER->Uniform("dirLight.ambient", ambient);
		SHADER->Uniform("dirLight.diffuse", diffuse);
		SHADER->Uniform("dirLight.specular", specular);
	}	

	

	static void SubmitModelToScene(const glm::mat4& model, const Geometries& vao, bool rotate = false)
	{
		SHADER->Uniform("normalMat", glm::inverse(glm::transpose(glm::mat3(model))));
		SHADER->Uniform("model", model);

		s_Data->VAO[vao]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[vao]);
	}

	

	void RendererGeometry::Init() // Inicializacion statica (1 instancia)
	{
		// Instancia de los recursos para las 
		s_Data = std::make_unique<RendererGeometryAssets>();

		// Librerias de shaders
		//s_Data->SLib.Load("Vuelta", "../shaders/3D/TEXTU/phong2pointlight.glsl");
		s_Data->SLib.Load("PhongT", "../assets/shaders/phong.glsl");
		s_Data->SLib.Load("ScreenTexture", "../assets/shaders/FBQuad.glsl");
		

		
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

		/////////////// SCREEN///////////////
		{
			Quad SCREEN(2.0f);
			s_Data->VAO[screen] = VAO::Create();

			RefCount<VBO> VBO_Screen = VBO::Create(SCREEN.Get(), SCREEN.SizeVBO());
			VBO_Screen->SetLayout(GetLayout());
			s_Data->VAO[screen]->Add__VBO(VBO_Screen);

			RefCount<EBO> EBO_Screen = std::make_shared<OpenGLEBO>(SCREEN.Indices(), SCREEN.SizeIndices());
			s_Data->VAO[screen]->Add__EBO(EBO_Screen);
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

	void RendererGeometry::EndScene() {	SHADER->Unbind(); ScreenTexture->Unbind(); }

	void RendererGeometry::DrawQuadScreenTexture(const RefCount<FrameBuffer>& fbotexture)
	{
		ScreenTexture->Bind();		

		fbotexture->ActiveTexture(0);
		ScreenTexture->Uniform("screenTexture", 0);

		s_Data->VAO[screen]->Bind();
		RenderDrawCall::Draw(s_Data->VAO[screen]);
	}	

	void RendererGeometry::BeginScene(const CameraFirstPerson& C)
	{

		SHADER->Bind();
		glm::mat4 view = glm::mat4(1.0f);
		view = C.Get().GetViewMatrix();
		SHADER->Uniform("view", view);		
		SHADER->Uniform("proj", glm::perspective
		(
			glm::radians
			(
				C.Get().GetFOV()),
				C.GetViewPort().x / C.GetViewPort().y,
				C.GetNear(), C.GetFar()
			)
		);	
		SHADER->Uniform("viewPos", C.Get().GetPosition());
		SHADER->Uniform("TFMviewPos", C.Get().GetPosition()); // NORMAL MAPPING

		
		
	}

	void RendererGeometry::DrawDirectionalLight(const LightComponent& L)
	{
		SettLight(L.Direction, L.Position, L.Ambient, L.Difusse, L.Specular);
	}

	// POINT LIGHTS
	void RendererGeometry::DrawPointLights(const PointLightComponent& PL, const glm::vec3& position, const uint32_t idx)
	{
		
		const std::string prefixPoint = "pointLight[";
		
			const std::string lightName = prefixPoint + std::to_string(idx) + "].";

			SHADER->Uniform((lightName + "position").c_str(),  position);
			SHADER->Uniform((lightName + "ambient").c_str(),   PL.Ambient);
			SHADER->Uniform((lightName + "diffuse").c_str(),   PL.Difusse);
			SHADER->Uniform((lightName + "specular").c_str(),  PL.Specular);
			 
			SHADER->Uniform((lightName + "constant").c_str(),  PL.Constant);
			SHADER->Uniform((lightName + "linear").c_str(),    PL.Linear);
			SHADER->Uniform((lightName + "quadratic").c_str(), PL.Quadratic);
					
	}

	void RendererGeometry::DrawSpotLights(const SpotLightComponent& SL, const glm::vec3& position, const glm::vec3& direction, const uint32_t idx)
	{
		const std::string prefixPoint = "spotLight[";
		
			const std::string lightName = prefixPoint + std::to_string(idx) + "].";
		
			SHADER->Uniform((lightName + "position").c_str(),  position);
			SHADER->Uniform((lightName + "direction").c_str(), direction);
			SHADER->Uniform((lightName + "ambient").c_str(),   SL.Ambient);
			SHADER->Uniform((lightName + "diffuse").c_str(),   SL.Difusse);
			SHADER->Uniform((lightName + "specular").c_str(),  SL.Specular);
															   
			SHADER->Uniform((lightName + "constant").c_str(),  SL.Constant);
			SHADER->Uniform((lightName + "linear").c_str(),    SL.Linear);
			SHADER->Uniform((lightName + "quadratic").c_str(), SL.Quadratic);
			SHADER->Uniform((lightName + "cutOff").c_str(),    glm::cos(glm::radians(SL.CutOff)));
			SHADER->Uniform((lightName + "outerCutOff").c_str(), glm::cos(glm::radians(SL.OuterCutOff)));
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
		SetTexture(*texture.Albedo, *texture.Specular, *texture.Normal, texture.Shininess);
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
		SetTexture(*texture.Albedo, *texture.Specular, *texture.Normal, texture.Shininess);
		SubmitModelToScene(model, quad);
	}



	// CUBES
	void RendererGeometry::DrawCube(const glm::mat4& trans, const MaterialComponent& m, bool rotate)
	{
		
		glm::mat4 model = trans;
		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
		SubmitModelToScene(model, cube);
	}
	void RendererGeometry::DrawCube(const glm::mat4& trans, const TextureComponent& texture, bool rotate)
	{
		glm::mat4 model = trans;		
		SetTexture(*texture.Albedo, *texture.Specular, *texture.Normal, texture.Shininess);
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
		SetTexture(*texture.Albedo, *texture.Specular, *texture.Normal, texture.Shininess);
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
		SetTexture(*texture.Albedo, *texture.Specular, *texture.Normal, texture.Shininess);
		SubmitModelToScene(model, teapot);
	}
}

//#include "../src/engine/mhpch.cpp"
//#include "engine/system/renderer/RendererGeometry.hpp"
//#include "engine/system/renderer/VAO.hpp"
//#include "engine/system/utils/Library.hpp"
//#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
//#include <engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "engine/Engine.hpp"
//
//#define W_ static_cast<float>(Engine::p().GetWindow().GetWidth())
//#define H_ static_cast<float>(Engine::p().GetWindow().GetHeight())
//
//#define SHADER std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("Vuelta"))
//
//// #define SHADER std::reinterpret_pointer_cast<OpenGLShader>(s_Data->SLib.Get("PhongT"))
//
//
//namespace MHelmet
//{
//
//	enum  Geometries { triangle = 0, quad, cube, sphere, teapot };
//
//	struct RendererGeometryAssets
//	{
//		RefCount<VAO> VAO[5];
//		ShaderLib SLib; // SHADER LIBRARY // La idea es textura o color
//
//		RefCount<Texture2D> WhiteTextu;
//	};
//	static Unique<RendererGeometryAssets> s_Data;
//
//	static BUFFER::Layout GetLayout()
//	{
//		BUFFER::Layout layout =
//		{
//			{BUFFER::DataType::Float3, "a_Pos"         },
//			{BUFFER::DataType::Float2, "a_UVS"         },
//			{BUFFER::DataType::Float3, "a_Normals"     },
//			{BUFFER::DataType::Float3, "a_Tangents"    },
//			{BUFFER::DataType::Float3, "a_BiTangents"  }
//		};
//		return layout;
//	}
//
//	static void SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const int& shininess)
//	{
//
//		SHADER->Uniform("u_IsMaterial", 1);
//		SHADER->Uniform("u_material.ambient", ambient);
//		SHADER->Uniform("u_material.diffuse", diffuse);
//		SHADER->Uniform("u_material.specular", specular);
//		SHADER->Uniform("u_material.shininess", shininess);
//	}
//	static void SetTexture(const Texture2D& albedo, const Texture2D& specular)
//	{
//		SHADER->Uniform("u_IsMaterial", 0);
//		albedo.Bind(0);
//		SHADER->Uniform("u_matTexture.diffuse", 0);
//		specular.Bind(1);
//		SHADER->Uniform("u_matTexture.specular", 1);
//	}
//
//	static void SettLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
//	{
//		SHADER->Uniform("u_light.direction", direction);
//		SHADER->Uniform("u_light.ambient", ambient);
//		SHADER->Uniform("u_light.diffuse", diffuse);
//		SHADER->Uniform("u_light.specular", specular);
//	}
//
//	static void SubmitModelToScene(const glm::mat4& model, const Geometries& vao)
//	{
//		SHADER->Uniform("u_normalMat", glm::inverse(glm::transpose(glm::mat3(model))));
//		SHADER->Uniform("u_model", model);
//
//		s_Data->VAO[vao]->Bind();
//		RenderDrawCall::Draw(s_Data->VAO[vao]);
//	}
//
//	void RendererGeometry::Init() // Inicializacion statica (1 instancia)
//	{
//		// Instancia de los recursos para las 
//		s_Data = std::make_unique<RendererGeometryAssets>();
//
//		// Librerias de shaders
//		s_Data->SLib.Load("Vuelta", "../shaders/3D/TEXTU/phong2pointlight.glsl");
//		s_Data->SLib.Load("PhongT", "../shaders/3D/TEXTU/phong2.glsl");
//
//
//		/////////////// Triangle ///////////////
//		{
//			Triangle T;
//			s_Data->VAO[triangle] = VAO::Create();
//
//			RefCount<VBO> VBO_T = VBO::Create(T.Get(), T.SizeVBO());
//			VBO_T->SetLayout(GetLayout());
//			s_Data->VAO[triangle]->Add__VBO(VBO_T);
//
//			RefCount<EBO> EBO_T = std::make_shared<OpenGLEBO>(T.Indices(), T.SizeIndices());
//
//			s_Data->VAO[triangle]->Add__EBO(EBO_T);
//		}
//
//		/////////////// Quad ///////////////
//		{
//			Quad Q(1.0f);
//			s_Data->VAO[quad] = VAO::Create();
//
//			RefCount<VBO> VBO_Q = VBO::Create(Q.Get(), Q.SizeVBO());
//			VBO_Q->SetLayout(GetLayout());
//			s_Data->VAO[quad]->Add__VBO(VBO_Q);
//
//			RefCount<EBO> EBO_Q = std::make_shared<OpenGLEBO>(Q.Indices(), Q.SizeIndices());
//			s_Data->VAO[quad]->Add__EBO(EBO_Q);
//		}
//
//		/////////////// Cube ///////////////
//		{
//			Cube C(1.0f);
//			s_Data->VAO[cube] = VAO::Create();
//
//			RefCount<VBO> VBO_C = VBO::Create(C.Get(), C.SizeVBO());
//			VBO_C->SetLayout(GetLayout());
//			s_Data->VAO[cube]->Add__VBO(VBO_C);
//
//			RefCount<EBO> EBO_C = std::make_shared<OpenGLEBO>(C.Indices(), C.SizeIndices());
//			s_Data->VAO[cube]->Add__EBO(EBO_C);
//		}
//
//
//		/////////////// Sphere ///////////////
//		{
//			Sphere S(1.0f, 50, 50);
//			s_Data->VAO[sphere] = VAO::Create();
//
//			RefCount<VBO> VBO_S = VBO::Create(S.Get(), S.SizeVBO());
//			VBO_S->SetLayout(GetLayout());
//			s_Data->VAO[sphere]->Add__VBO(VBO_S);
//
//			RefCount<EBO> EBO_S = std::make_shared<OpenGLEBO>(S.Indices(), S.SizeIndices());
//			s_Data->VAO[sphere]->Add__EBO(EBO_S);
//		}
//
//
//		/////////////// Teapot ///////////////
//		{
//			Teapot TP(50);
//			s_Data->VAO[teapot] = VAO::Create();
//
//			RefCount<VBO> VBO_TP = VBO::Create(TP.Get(), TP.SizeVBO());
//			VBO_TP->SetLayout(GetLayout());
//			s_Data->VAO[teapot]->Add__VBO(VBO_TP);
//
//			RefCount<EBO> EBO_TP = std::make_shared<OpenGLEBO>(TP.Indices(), TP.SizeIndices());
//			s_Data->VAO[teapot]->Add__EBO(EBO_TP);
//		}
//
//	}
//
//	void RendererGeometry::EndScene() { SHADER->Unbind(); }
//
//	//	void RendererGeometry::ShutDown() {}
//
//	void RendererGeometry::BeginScene(const CameraManComponent& C, const LightComponent& L)
//	{
//
//		SHADER->Bind();
//		glm::mat4 view = glm::mat4(1.0f);
//		view = C.Cameraman.Get().GetViewMatrix();
//		SHADER->Uniform("u_view", view);
//		SHADER->Uniform("u_proj", glm::perspective
//		(
//			glm::radians
//			(
//				C.Cameraman.Get().GetFOV()),
//			C.ViewportX / C.ViewportY,
//			C.Near, C.Far
//		)
//		);
//		SHADER->Uniform("u_viewPos", C.Cameraman.Get().GetPosition());
//
//		//SettLight(L.Direction, L.Ambient, L.Difusse, L.Specular);		
//	}
//
//	// POINT LIGHTS
//	void RendererGeometry::DrawPointLights(const PointLightComponent& PL, const uint32_t idx)
//	{
//		SHADER->Uniform("u_pointLight.position", PL.Position);
//		SHADER->Uniform("u_pointLight.ambient", PL.Ambient);
//		SHADER->Uniform("u_pointLight.diffuse", PL.Difusse);
//		SHADER->Uniform("u_pointLight.specular", PL.Specular);
//
//		SHADER->Uniform("u_pointLight.constant", PL.Constant);
//		SHADER->Uniform("u_pointLight.linear", PL.Linear);
//		SHADER->Uniform("u_pointLight.quadratic", PL.Quadratic);
//	}
//
//	void RendererGeometry::DrawSpotLights(const SpotLightComponent& SL, const uint32_t idx)
//	{
//	}
//
//	// TRIANGLES
//	void RendererGeometry::DrawTriangle(const glm::mat4& trans, const MaterialComponent& m)
//	{
//		glm::mat4 model = trans;
//		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
//		SubmitModelToScene(model, triangle);
//	}
//
//	void RendererGeometry::DrawTriangle(const glm::mat4& trans, const TextureComponent& texture)
//	{
//		glm::mat4 model = trans;
//		SetTexture(*texture.Albedo, *texture.Specular);
//		SubmitModelToScene(model, triangle);
//	}
//
//
//	// QUADS
//	void RendererGeometry::DrawQuad(const glm::mat4& trans, const MaterialComponent& m)
//	{
//		glm::mat4 model = trans;
//		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
//		SubmitModelToScene(model, quad);
//	}
//	void RendererGeometry::DrawQuad(const glm::mat4& trans, const TextureComponent& texture)
//	{
//		glm::mat4 model = trans;
//		SetTexture(*texture.Albedo, *texture.Specular);
//		SubmitModelToScene(model, quad);
//	}
//
//
//
//	// CUBES
//	void RendererGeometry::DrawCube(const glm::mat4& trans, const MaterialComponent& m)
//	{
//
//		glm::mat4 model = trans;
//		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
//		SubmitModelToScene(model, cube);
//	}
//	void RendererGeometry::DrawCube(const glm::mat4& trans, const TextureComponent& texture)
//	{
//		glm::mat4 model = trans;
//		SetTexture(*texture.Albedo, *texture.Specular);
//		SubmitModelToScene(model, cube);
//	}
//
//
//	// SPHERES
//	void RendererGeometry::DrawSphere(const glm::mat4& trans, const MaterialComponent& m)
//	{
//		glm::mat4 model = trans;
//		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
//		SubmitModelToScene(model, sphere);
//	}
//	void RendererGeometry::DrawSphere(const glm::mat4& trans, const TextureComponent& texture)
//	{
//		glm::mat4 model = trans;
//		SetTexture(*texture.Albedo, *texture.Specular);
//		SubmitModelToScene(model, sphere);
//	}
//
//
//
//	// TEAPOTS
//	void RendererGeometry::DrawTeapot(const glm::mat4& trans, const MaterialComponent& m)
//	{
//		glm::mat4 model = trans;
//		SetMaterial(m.Ambient, m.Difusse, m.Specular, m.Shininess);
//		SubmitModelToScene(model, teapot);
//	}
//
//	void RendererGeometry::DrawTeapot(const glm::mat4& trans, const TextureComponent& texture)
//	{
//		glm::mat4 model = trans;
//		SetTexture(*texture.Albedo, *texture.Specular);
//		SubmitModelToScene(model, teapot);
//	}
//}