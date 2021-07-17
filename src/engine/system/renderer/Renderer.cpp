#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include "engine/system/renderer/RendererGeometry.hpp"
#include "engine/system/renderer/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Engine.hpp"

namespace MHelmet
{
	void Renderer::Init()	
	{
		RenderDrawCall::Init();
		RendererGeometry::Init();
	}
}