#pragma once
#include <glm/glm.hpp>

namespace MHelmet
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top);

		

		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		void SetRotation(float rotation) { m_Rotation = rotation; }

		const glm::vec3& GetPosition() { return m_Position; }
		float GetRotation() { return m_Rotation; }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}