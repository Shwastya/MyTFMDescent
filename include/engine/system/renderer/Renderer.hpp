#pragma once
#include "engine/system/renderer/RenderDrawCall.hpp"
#include "PerspectiveCamera.hpp"
//#define SHADER std::reinterpret_pointer_cast<OpenGLShader>(_Shader)

namespace MHelmet
{	
	class Renderer
	{
	public:

		static void BeginModel(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float degrees);
		static void BeginScene(RefCount<PerspectiveCamera>& camera);
		static void EndEscene();

		// se anyade material pero solo es un vec4 que pasa el color
		// la idea es de momento hacerlo simple pero en el futuro 
		// lo que se le deberia pasar es un tipo de clase material 
		// que pueda englobar tanto colores como texturas 
		// haciendo las abstracciones necesarias con factory method 
		// y switch hacia distintos contextos de render 
		static void Material(const RefCount<Shader>& _Shader, const glm::vec3& material);
		//	static void SetTexture();
		static void Submit(const RefCount<Shader>& _Shader, const RefCount<VAO>& _VAO);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct DataScene
		{
			glm::mat4 Projection;
			glm::mat4 Model;
			glm::mat4 View;

			//glm::mat4 ViewMatrixRefresh;
		};

		static DataScene* Scene;
		static PerspectiveCamera* camera;
	};

	
}