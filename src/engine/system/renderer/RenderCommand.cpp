//#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/RenderCommand.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLRendererAPI.hpp"

namespace MHelmet
{
	RendererAPI* RenderCommand::s_RenderererAPI = new OpenGlRendererAPI();
}