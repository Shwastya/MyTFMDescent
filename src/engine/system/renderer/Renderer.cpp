#include "engine/system/renderer/Renderer.hpp"
#include "engine/Engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#define SHADER std::reinterpret_pointer_cast<OpenGLShader>
#define W_WIDTH  static_cast<float>(Engine::p().GetWindow().GetWidth())
#define W_HEIGHT static_cast<float>(Engine::p().GetWindow().GetHeight())


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

		Scene->View = glm::mat4(1.0f);
		Scene->View = camera.GetViewMatrix();

		Scene->Projection = glm::perspective(glm::radians(camera.GetFOV()), W_WIDTH / W_HEIGHT,	0.1f, 100.0f);

	}
	void Renderer::EndEscene()
	{
		delete Renderer::Scene;
	}
	void Renderer::Bind(const RefCount<Shader>& _Shader)
	{
		SHADER(_Shader)->Bind();
	}
	void Renderer::Uniform(const RefCount<Shader>& _Shader, const char* u_name, const glm::vec3& material)
	{
		// vec3
		SHADER(_Shader)->Uniform(u_name, material);
	}

	void Renderer::Uniform(const RefCount<Shader>& _Shader, const char* u_name, const float value)
	{
		// float
		SHADER(_Shader)->Uniform(u_name, value);
	}

	void Renderer::Uniform(const RefCount<Shader>& _Shader, const char* u_name, const int value)
	{
		// int
		SHADER(_Shader)->Uniform(u_name, value);
	}


	void Renderer::Texture(const RefCount<Shader>& _Shader, const RefCount<Texture2D>& texture, uint32_t unit)
	{
		texture->Bind(unit);
		SHADER(_Shader)->Uniform("u_Texture", static_cast<int32_t>(unit));

	}	

	void Renderer::NormalMat(const RefCount<Shader>& _Shader)
	{
		

		glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(Scene->Model)));
		
		SHADER(_Shader)->Uniform("u_normalMat", normalMat);
	}
	
	void Renderer::Submit(const RefCount<Shader>& _Shader, const RefCount<VAO>& _VAO)
	{
		// Antes de hacer el submit hay que insertar un material o una textura

		

		//SHADER(_Shader)->Uniform("u_AmbientStrength", 0.2f);

		SHADER(_Shader)->Uniform("u_model", Scene->Model);
		SHADER(_Shader)->Uniform("u_view", Scene->View);
		SHADER(_Shader)->Uniform("u_proj", Scene->Projection);

		_VAO->Bind();
		RenderDrawCall::Draw(_VAO);

		//SHADER(_Shader)->Unbind();
	}
}