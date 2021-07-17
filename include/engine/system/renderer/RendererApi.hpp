#pragma once
#define STB_IMAGE_IMPLEMENTATION 


#include <glm/glm.hpp>
#include "engine/system/renderer/shader.hpp" 
#include "engine/system/renderer/VAO.hpp"

namespace MHelmet
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX = 2, Vulkan = 3
		};

	public:
		virtual void Init() = 0;
		virtual void ClearColor(const glm::vec4& color) = 0;

		virtual void clear() = 0;
		virtual void ClearColorBufferOnly() = 0;
		virtual void ClearDepthBufferOnly() = 0;

		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
		virtual void Draw(const RefCount<VAO>& _VAO) = 0;

		
		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;		
		
		static API GetAPI() { return s_API; }

		//static void SetAPI(RendererAPI::API rendererAPI = RendererAPI::API::OpenGL);
		virtual std::string GetVendor()   const = 0;
		virtual std::string GetRenderer() const = 0;
		virtual std::string GetVersion()  const = 0;

	private:
		const static API s_API{ API::OpenGL }; // de momento OpenGL constante		
	};


}