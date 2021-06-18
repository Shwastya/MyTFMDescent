#include "engine/system/renderer/Renderer.hpp"
#include "engine/Engine.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"



namespace MHelmet
{	
	Renderer::DataScene* Renderer::Scene = new Renderer::DataScene;
		
	void Renderer::Init()
	{
		RenderDrawCall::Init();
	}

	void Renderer::Model(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float degrees)
	{
		
		Scene->Model = glm::mat4(1.0f);
		Scene->Model = glm::translate(Scene->Model, translate); 	
		Scene->Model = glm::rotate(Scene->Model, degrees, rotate);
		Scene->Model = glm::scale(Scene->Model, scale);
	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{	
		
		Scene->View  = glm::mat4(1.0f);		
		Scene->View = camera.GetViewMatrix();

		Scene->Projection = glm::perspective
		(
			glm::radians(camera.GetFOV()), 
			static_cast<float>(Engine::p().GetWindow().GetWidth()) / 
			static_cast<float>(Engine::p().GetWindow().GetHeight()), 
			0.1f, 100.0f
		);

	}
	void Renderer::EndEscene()
	{
		delete Renderer::Scene;
	}
	void Renderer::Material(const RefCount<Shader>& _Shader, const glm::vec3& material)
	{
		SHADER(_Shader)->Bind();
		SHADER(_Shader)->Uniform("u_Color", material);
	}
	void Renderer::Texture(const RefCount<Shader>& _Shader, const RefCount<Texture2D>& texture, uint32_t unit)
	{
		
		SHADER(_Shader)->Bind();
		texture->Bind(unit);
		SHADER(_Shader)->Uniform("u_Texture", static_cast<int32_t>(unit));
		
	}
	void Renderer::Submit(const RefCount<Shader>& _Shader, const RefCount<VAO>& _VAO)
	{
		// Antes de hacer el submit hay que insertar un material o una textura

		SHADER(_Shader)->Uniform("u_Model", Scene->Model);
		SHADER(_Shader)->Uniform("u_View", Scene->View);
		SHADER(_Shader)->Uniform("u_Proj", Scene->Projection);

		_VAO->Bind();
		RenderDrawCall::Draw(_VAO);
	}
}