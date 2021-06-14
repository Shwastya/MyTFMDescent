#include "engine/system/renderer/Renderer.hpp"
#include "engine/Engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace MHelmet
{	
	Renderer::DataScene* Renderer::Scene = new Renderer::DataScene;
	//PerspectiveCamera* camera = new PerspectiveCamera(glm::vec3(0.0f, 0.0f, 3.0f));
		
	void Renderer::BeginScene(std::shared_ptr<PerspectiveCamera>& camera)
	{	
		Scene->Model = glm::mat4(1.0f);
		Scene->Model = glm::rotate(Scene->Model, static_cast<float>(glfwGetTime()) * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		Scene->View  = glm::mat4(1.0f);
		Scene->View  = glm::translate(Scene->View, glm::vec3(0.0f, 0.0f, -3.0f));

		
		Scene->Projection = glm::perspective
		(
			glm::radians(camera->GetFOV()), 
			static_cast<float>(Engine::p().GetWindow().GetWidth()) / 
			static_cast<float>(Engine::p().GetWindow().GetHeight()), 
			0.1f, 100.0f
		);

		Scene->ViewMatrixRefresh = camera->GetViewMatrix();
	}
	void Renderer::EndEscene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<Shader>& _Shader, const std::shared_ptr<VAO>& _VAO)
	{
		_Shader->Bind();

		
		_Shader->SetUniform("u_Model", Scene->Model);
		_Shader->SetUniform("u_View", Scene->ViewMatrixRefresh);
		_Shader->SetUniform("u_Proj", Scene->Projection);

		_VAO->Bind();
		RenderCommand::DrawIndexed(_VAO);
	}
}