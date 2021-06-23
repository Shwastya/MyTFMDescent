#pragma once
#include <glm/glm.hpp>

namespace MHelmet
{
	struct TransformComponent
	{
		glm::vec3 T = glm::vec3(0.0f);
		glm::vec3 R = glm::vec3(1.0f);
		glm::vec3 S = glm::vec3(1.0f);
		float Degrees = 0.0f;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform, const glm::vec3& _t, const glm::vec3& _r, const glm::vec3& _s)
			: T(_t), R(_r), S(_s) {}

		//operator glm::mat4& () { return Transform; }
		//operator const glm::mat4& () { return Transform; }

	};

	/* MATERIALS COMPONENT */
	// u_material.ambient
	// u_material.diffuse 
	// u_material.specular
	// u_material.shininess
	struct MaterialComponent // u_material.ambient
	{
		glm::vec3 Ambient  = glm::vec3{ 1.0f, 0.5f, 0.31f };
		glm::vec3 Difusse  = glm::vec3{ 1.0f, 0.5f, 0.31f };
		glm::vec3 Specular = glm::vec3{ 0.5f, 0.5f, 0.5f  };
		int Shininess = 32;

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const glm::vec3& ambient, const glm::vec3& difusse, const glm::vec3& specular, const int& shininess)
			: Ambient(ambient), Difusse(difusse), Specular(specular), Shininess(shininess) {}

		//operator glm::vec3& () { return Material; }
		//operator const glm::vec3& () { return Material; }
	};


}
	/* LIGHTS COMPONENT */
	// u_light.position
	// u_light.ambient
	// u_light.diffuse
	// u_light.specular
	struct LightComponent 
	{
		glm::vec3 Light = glm::vec3{ 0.0f, 6.0f, 3.0f };

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(const glm::vec3 & light)
			: Light(light) {}

		//operator glm::vec3& () { return Light; }
		operator const glm::vec3& () { return Light; }
	};


	