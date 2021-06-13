#include "engine/system/renderer/Renderer.hpp"


namespace MHelmet
{	
	void Renderer::BeginScene()
	{

	}
	void Renderer::EndEscene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<VAO>& _VAO)
	{
		_VAO->Bind();
		RenderCommand::DrawIndexed(_VAO);
	}
}