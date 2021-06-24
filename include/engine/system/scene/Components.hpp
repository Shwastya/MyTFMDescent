#pragma once
#include <glm/glm.hpp>
#include "engine/system/renderer/PerspectiveCamera.hpp"

namespace MHelmet
{	
	struct TransformComponent
	{
		glm::vec3 T = glm::vec3(0.0f);
		glm::vec3 R = glm::vec3(1.0f);
		glm::vec3 S = glm::vec3(1.0f);
		float Degrees = 0.3f;

		bool IsDirty = true;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform, const glm::vec3& _t, const glm::vec3& _r, const glm::vec3& _s)
			: T(_t), R(_r), S(_s) {}

		//operator glm::mat4& () { return Transform; }
		//operator const glm::mat4& () { return Transform; }

	};

	struct CameraManComponent
	{


		CameraMan Cameraman = glm::vec3(0.0f, 1.0f, 6.5f);
		
		float ViewportX = 0.0f;
		float ViewportY = 0.0f;

		
		float Near = 0.1f;
		float Far = 100.0f;

		bool Primary = true; // igual se mueve a la scena o scena de camera

		bool IsHovered = true;
		bool IsDirty = true;


		CameraManComponent() = default;
		CameraManComponent(const CameraManComponent&) = default;
		CameraManComponent(const CameraMan& _camera, const float viewport_X, const float viewport_Y, const float& _near = 0.1f, const float& _far = 100.0f)
			: Cameraman(_camera), ViewportX(viewport_X), ViewportY(viewport_Y), Near(_near), Far(_far)  {}

		//operator glm::vec3& () { return Material; }
		//operator const CameraMan& () { return Cameraman; }

	};

	struct LightComponent
	{
		glm::vec3 Position = glm::vec3{ 0.0f, 10.0f, 12.0f };
		glm::vec3 Ambient = glm::vec3{ 0.3f, 0.3f, 0.3f };
		glm::vec3 Difusse = glm::vec3{ 0.5f, 0.5f, 0.5f };
		glm::vec3 Specular = glm::vec3{ 1.0f, 1.0f, 1.0f };

		bool IsDirty = true;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& difusse, const glm::vec3& specular)
			: Position(pos), Ambient(ambient), Difusse(difusse), Specular(specular) {}

		//operator glm::vec3& () { return Light; }
		operator const glm::vec3& () { return Position; }
	};

	
	struct MaterialComponent // u_material.ambient
	{
		glm::vec3 Ambient  = glm::vec3{ 1.0f, 0.5f, 0.31f };
		glm::vec3 Difusse  = glm::vec3{ 1.0f, 0.5f, 0.31f };
		glm::vec3 Specular = glm::vec3{ 0.5f, 0.5f, 0.5f  };
		int Shininess	   = 32;

		bool IsDirty = true;

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const glm::vec3& ambient, const glm::vec3& difusse, const glm::vec3& specular, const int& shininess)
			: Ambient(ambient), Difusse(difusse), Specular(specular), Shininess(shininess) {}

		//operator glm::vec3& () { return Material; }
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
}
	
	

	