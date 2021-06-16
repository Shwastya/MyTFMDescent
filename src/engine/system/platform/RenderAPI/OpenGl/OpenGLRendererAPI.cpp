#include "engine/system/platform/RenderAPI/OpenGL/OpenGLRendererAPI.hpp"
#include <glad/glad.h>

namespace MHelmet 
{
	void OpenGlRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.r, color.a);
	}
	
	void OpenGlRendererAPI::clear() // clear the color and the depth buffer // Temporal
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGlRendererAPI::DrawIndexed(const RefCount<VAO>& _VAO)
	{
		glDrawElements(GL_TRIANGLES, _VAO->GetEBO()->Count(), GL_UNSIGNED_INT, nullptr);
	}
}

