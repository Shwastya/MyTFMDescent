#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Window.hpp"
#include "engine/system/node/NodeLayer.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"

#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/Input.hpp"

#include "engine/system/shader.hpp" // temporal
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"
#include "engine/system/renderer/VAO.hpp"

#include "engine/system/renderer/OrthographicCamera.hpp"
#include "engine/system/renderer/PerspectiveCamera.hpp"

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

		/* para esto es singleton Engine */
		static Engine& p() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
		std::shared_ptr<PerspectiveCamera>& GetCamera(){ return m_Camera; }

		
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


		/*std::shared_ptr<Shader> m_Shader_Test;
		std::shared_ptr<VAO> m_VAO_Test;*/
		
		std::shared_ptr<PerspectiveCamera> m_Camera;

		/* TEMPORAL ????? */
		glm::mat4 m_Model = glm::mat4(1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);

	private:
		// necesito pasar el window al ImgUI Layer
		static Engine* s_Instance;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


