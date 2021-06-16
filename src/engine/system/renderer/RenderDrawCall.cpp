//#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/RenderDrawCall.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLRendererAPI.hpp"

namespace MHelmet
{
	RendererAPI* RenderDrawCall::s_RenderererAPI = new OpenGlRendererAPI();
}