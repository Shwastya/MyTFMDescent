#pragma once
#include <glm/glm.hpp>

namespace MHelmet
{
	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: Transform(transform) {}

		//operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () { return Transform; }

	};


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


	/* MATERIALS COMPONENT */
	// u_material.ambient
	// u_material.diffuse 
	// u_material.specular
	// u_material.shininess
	struct MaterialComponent // u_material.ambient
	{
		glm::vec3 Material = glm::vec3{ 0.3f, 0.5f, 0.4f };

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const glm::vec3 & material)
			: Material(material) {}

		operator glm::vec3& () { return Material; }
		operator const glm::vec3& () { return Material; }
	};

	
}