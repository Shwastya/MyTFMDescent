#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/system/renderer/PerspectiveCamera.hpp"
#include "engine/system/renderer/Texture.hpp"

//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace MHelmet
{	

	struct CameraManComponent
	{
		CameraMan Cameraman;

		float ViewportX = 0.0f;
		float ViewportY = 0.0f;


		float Near = 0.1f;
		float Far = 100.0f;

		bool Primary = true; // igual se mueve a la scena o scena de camera

		bool IsHovered = true;
		bool IsDirty = true;


		CameraManComponent() = default;
		CameraManComponent(const CameraManComponent&) = default;
		CameraManComponent(const CameraMan& _camera = glm::vec3(0.0f, 1.0f, 6.5f), const float viewport_X = 0.0f, const float viewport_Y = 0.0f, const float& _near = 0.1f, const float& _far = 100.0f)
			: Cameraman(_camera), ViewportX(viewport_X), ViewportY(viewport_Y), Near(_near), Far(_far) {}

	};


	struct TransformComponent
	{
		glm::vec3 T = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 R = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 S = glm::vec3(1.0f, 1.0f, 1.0f);	

		//bool IsDirty = true; // de momento sin flags
		uint32_t ID = 0;
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation, const uint32_t id = 0)
			: T(translation), ID(id) {}

		glm::mat4 GetTransform() const		{
			glm::mat4 rotation = glm::toMat4(glm::quat(R));
			return  glm::translate(glm::mat4(1.0f), T) 
				* rotation 
				* glm::scale(glm::mat4(1.0f), S);
		}
	};

	//struct LightComponent
	//{
	//	glm::vec3 Position = glm::vec3{ -3.0f, 4.0f, 1.0f };
	//	glm::vec3 Ambient = glm::vec3{ 0.6f, 0.6f, 0.6f };
	//	glm::vec3 Difusse = glm::vec3{ 1.0f, 1.0f, 1.0f };
	//	glm::vec3 Specular = glm::vec3{ 0.8f, 0.8f, 0.8f };

	//	bool IsDirty = true;

	//	LightComponent() = default;
	//	LightComponent(const LightComponent&) = default;
	//	LightComponent(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& difusse, const glm::vec3& specular)
	//		: Position(pos), Ambient(ambient), Difusse(difusse), Specular(specular) {}

	//	//operator glm::vec3& () { return Light; }
	//	operator const glm::vec3& () { return Position; }
	//};

	

	struct LightComponent
	{

		glm::vec3 Position = glm::vec3{ -3.0f, 4.0f, 1.0f }; // orientativo

		glm::vec3 Direction = glm::vec3{ 0.0f, -1.0f, 0.0f };
		glm::vec3 Ambient = glm::vec3{ 0.02f, 0.02f, 0.02f };
		glm::vec3 Difusse = glm::vec3{ 0.1f, 0.1f, 0.1f };
		glm::vec3 Specular = glm::vec3{ 0.2f, 0.2f, 0.2f };	

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(const glm::vec3& dir)
			: Direction(dir) {}
		
		glm::vec3& GetPosition() { return Position; }
		//operator glm::vec3& () { return Light; }
		operator const glm::vec3& () { return Direction; }
	};

	struct SpotLightComponent
	{

		glm::vec3 Position = glm::vec3{ -2.0f, 4.0f, 1.0f }; // orientativo

		glm::vec3 Direction = glm::vec3{ -0.2f, -1.0f, 0.0f };
		glm::vec3 Ambient = glm::vec3{ 0.6f, 0.6f, 0.6f };
		glm::vec3 Difusse = glm::vec3{ 0.0f, 0.0f, 0.4f };
		glm::vec3 Specular = glm::vec3{ 0.4f, 0.8f, 0.8f };

		float Constant = 1.0f; // const??
		float Linear = 0.09f;
		float Quadratic = 0.032;
		float CutOff = 30.0f;
		float outerCutOff = 40.0f;

		SpotLightComponent() = default;
		SpotLightComponent(const SpotLightComponent&) = default;
		SpotLightComponent(const glm::vec3& dir)
			: Direction(dir) {}

		operator glm::vec3& () { return Position; }
			
	};

	struct PointLightComponent
	{
		glm::vec3 Position = glm::vec3{ 2.0f, 2.0f, 0.0f };
		glm::vec3 Ambient = glm::vec3{ 0.02f, 0.02f, 0.02f };
		glm::vec3 Difusse = glm::vec3{ 0.2f, 0.0f, 0.0f };
		glm::vec3 Specular = glm::vec3{ 0.5f, 0.0f, 0.0f };

		float Constant = 1.0f; // const??
		float Linear = 0.09f;
		float Quadratic = 0.032;

		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;
		PointLightComponent(const glm::vec3 & pos)
			: Position(pos){}

		operator glm::vec3& () { return Position; }
	};

	struct MaterialComponent // u_material.ambient
	{


		glm::vec3 Ambient  = glm::vec3{ 0.5f, 0.0f, 0.0f };
		glm::vec3 Difusse  = glm::vec3{ 0.5f, 0.0f, 0.0f };
		glm::vec3 Specular = glm::vec3{ 0.7f, 0.6f, 0.6f };
		int Shininess	   = 32;


		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const glm::vec3& ambient, const glm::vec3& difusse, const glm::vec3& specular, const int& shininess)
			: Ambient(ambient), Difusse(difusse), Specular(specular), Shininess(shininess) {}

		void SetDefault()
		{
			Ambient = glm::vec3(1.0f, 1.0f, 1.0f); Difusse = glm::vec3(0.296648f, 0.296648f, 0.296648f), Specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
		}

		operator glm::vec3& () { return Ambient; }
		//operator const glm::vec3& () { return Material; }
	};

	

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		//operator glm::vec3& () { return Light; }
		operator const std::string& () { return Tag; }
	};

	struct TextureComponent
	{
		// default textures
		std::string P_A;
		std::string P_S;
		std::string P_N; 

		std::string D_A = "../assets/textures/bricks_albedo.png";
		std::string D_S = "../assets/textures/bricks_specular.png"; ;
		std::string D_N = "../assets/textures/bricks_normal.png";

		Texture2D::Format Format = Texture2D::Format::RGB;

		RefCount<Texture2D> Albedo;
		RefCount<Texture2D> Specular;
		RefCount<Texture2D> Normal;

		int Shininess = 32;
		
		TextureComponent() = default;
		TextureComponent(const TextureComponent&) = default;
		TextureComponent(Texture2D::Format format = Texture2D::Format::RGB)
			: Format(format) 
		{
			P_A = D_A; P_S = D_S; P_N = D_N;
		}

		void SetAlbedo()
		{
			//Albedo = nullptr;
			Albedo = Texture2D::Create(P_A, Format);
		}
		void SetSpecular()
		{
		//	Specular = nullptr;
			Specular = Texture2D::Create(P_S, Format);
		}

		void SetNormal()
		{
			//Normal = nullptr;
			Normal = Texture2D::Create(P_N, Format);
		}

		void SetComponentTexture()
		{
			Albedo = Texture2D::Create("../assets/textures/bricks_albedo.png", Format);
			Specular = Texture2D::Create("../assets/textures/bricks_specular.png", Format);
			Normal = Texture2D::Create("../assets/textures/bricks_normal.png", Format);
			SetAlbedo();
			SetSpecular();
			SetNormal();				
		}

		void SetToDefault()
		{
			P_A = D_A; P_S = D_S; P_N = D_N;
		}

		operator int& () { return Shininess; }

	};
}
	
	

	