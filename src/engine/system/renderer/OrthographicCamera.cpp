#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace MHelmet
{
	OrthograpicCamera::OrthograpicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
		, m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthograpicCamera::RecalculateViewMatrix()
	{
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(tranform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}