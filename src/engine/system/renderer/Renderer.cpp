#include "engine/system/renderer/Renderer.hpp"
#include "engine/Engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"

namespace MHelmet
{	
	Renderer::DataScene* Renderer::Scene = new Renderer::DataScene;
	//PerspectiveCamera* camera = new PerspectiveCamera(glm::vec3(0.0f, 0.0f, 3.0f));
		
	void Renderer::BeginModel(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float degrees)
	{
		
		Scene->Model = glm::mat4(1.0f);
		Scene->Model = glm::translate(Scene->Model, translate); 	
		Scene->Model = glm::rotate(Scene->Model, degrees, rotate);
		Scene->Model = glm::scale(Scene->Model, scale);
	}

	void Renderer::BeginScene(RefCount<PerspectiveCamera>& camera)
	{	
		
		Scene->View  = glm::mat4(1.0f);		
		Scene->View = camera->GetViewMatrix();

		Scene->Projection = glm::perspective
		(
			glm::radians(camera->GetFOV()), 
			static_cast<float>(Engine::p().GetWindow().GetWidth()) / 
			static_cast<float>(Engine::p().GetWindow().GetHeight()), 
			0.1f, 100.0f
		);

		//Scene->ViewMatrixRefresh = camera->GetViewMatrix();
	}
	void Renderer::EndEscene()
	{

	}
	void Renderer::Submit(const RefCount<Shader>& _Shader, const RefCount<VAO>& _VAO, const glm::vec3& material)
	{
		// std::reinterpret_pointer_cast<OpenGLShader>(_Shader)->Bind();

		 _Shader->Bind();

		 std::reinterpret_pointer_cast<OpenGLShader>(_Shader)->SetUniform("u_Color", material);

		 std::reinterpret_pointer_cast<OpenGLShader>(_Shader)->SetUniform("u_Model", Scene->Model);
		 std::reinterpret_pointer_cast<OpenGLShader>(_Shader)->SetUniform("u_View", Scene->View);
		 std::reinterpret_pointer_cast<OpenGLShader>(_Shader)->SetUniform("u_Proj", Scene->Projection);

		_VAO->Bind();
		RenderDrawCall::DrawIndexed(_VAO);
	}
}