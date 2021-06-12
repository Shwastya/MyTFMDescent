#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Window.hpp"
#include "engine/system/node/NodeLayer.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"

#include "engine/system/events/AppEvents/OnAppEvents.hpp"

#include "engine/system/shader.hpp" // temporal
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"
#include "engine/system/renderer/VAO.hpp"

namespace MHelmet 
{

	class Engine 
	{

	public:

		Engine();
		virtual ~Engine();

		void run();

		void OnEvent(Event& event);

		void PushLayer(NodeLayer* layer);
		void PushOverlay(NodeLayer* layer);


		inline static Engine& p() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		
	private: 
		bool WindowCloseTask(OnWindowClose& e); // perform event

	private:
		std::unique_ptr<Window>	m_Window;
		
		bool m_Alive = true;
		LayerManager  m_Layers;
		ImGuiLayer* m_ImGuiLayers;

		

		//uint32_t m_VAO;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VAO> m_VAO;
		std::shared_ptr<VBO> m_VBO;		
		std::shared_ptr<EBO> m_EBO;


		std::shared_ptr<Shader> m_Shader_Test;
		std::shared_ptr<VAO> m_VAO_Test;
		std::shared_ptr<VBO> VBO_Test;
		std::shared_ptr<EBO> EBO_Test;
		


	private:
		// necesito pasar el window al ImgUI Layer
		static Engine* s_Instance;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


