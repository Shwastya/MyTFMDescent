#include "engine/system/platform/RenderAPI/OpenGL/OpenGLRendererAPI.hpp"
#include <glad/glad.h>

namespace MHelmet 
{

	void OpenGlRendererAPI::Init()
	{
		// Se habilita el Alpha Blending para imagenes PNG con transparencia
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Se habilita el test de profundidad para las geometrias 3D
		glEnable(GL_DEPTH_TEST);
		// (el mas habitual) el que tiene la prof. mas pequenya es el que queda
		glDepthFunc(GL_LESS); 


		// Se habilita el CULL_FACE para ahorrarse el pintado de las caras traseras
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);		
	}


	void OpenGlRendererAPI::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.r, color.a);
	}
	
	void OpenGlRendererAPI::clear() // clear the color and the depth buffer // Temporal
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGlRendererAPI::Draw(const RefCount<VAO>& _VAO)
	{

		glDrawElements(GL_TRIANGLES, _VAO->GetEBO()->Count(), GL_UNSIGNED_INT, nullptr);
	}
}

