#pragma once
#include "engine/system/renderer/RenderDrawCall.hpp"
#include "PerspectiveCamera.hpp"
#include "engine/system/renderer/Texture.hpp"

#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>
#define W_WIDTH  static_cast<float>(Engine::p().GetWindow().GetWidth())
#define W_HEIGHT static_cast<float>(Engine::p().GetWindow().GetHeight())

namespace MHelmet
{	
	class Renderer
	{
	public:

		static void Init();

		static void Model(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float degrees);
		static void BeginScene(PerspectiveCamera& camera);
		static void EndEscene();

		// se anyade material pero solo es un vec4 que pasa el color
		// la idea es de momento hacerlo simple pero en el futuro 
		// lo que se le deberia pasar es un tipo de clase material 
		// que pueda englobar tanto colores como texturas 
		// haciendo las abstracciones necesarias con factory method 
		// y switch hacia distintos contextos de render 
		static void Bind(const RefCount<Shader>& _Shader);

		template <typename T>
		static void Uniform(const RefCount<Shader>& _Shader, const char* u_name, const T& value);

		static void Uniform(const RefCount<Shader>& _Shader, const char* u_name, const glm::vec3& material);		
		static void Uniform(const RefCount<Shader>& _Shader, const char* u_name, float value);
		static void Uniform(const RefCount<Shader>& _Shader, const char* u_name, int value);
		static void Texture (const RefCount<Shader>& _Shader, const RefCount<Texture2D>& texture, uint32_t unit);
		
		static void NormalMat(const RefCount<Shader>& _Shader);
		static void Submit(const RefCount<Shader>& _Shader, const RefCount<VAO>& _VAO);


		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct DataScene
		{
			glm::mat4 Projection;
			glm::mat4 Model;
			glm::mat4 View;

			//float AmbientStrength = 0.2f; // default ambient

			//glm::mat4 ViewMatrixRefresh;
		};

		static DataScene* Scene;
		static PerspectiveCamera* camera;
	};

	
	template<typename T>
	inline void Renderer::Uniform(const RefCount<Shader>& _Shader, const char* u_name, const T& value)
	{
	}

}