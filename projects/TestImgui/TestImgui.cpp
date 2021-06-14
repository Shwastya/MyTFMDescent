#include <MHelmet.h>

/**************************************
*       Proyecto Cliente Layer        *
* *************************************/
//class ImGuiLayer;

class TestingLayer : public MHelmet::NodeLayer
{
public:
	TestingLayer() : MHelmet::NodeLayer("TestingLayer")
	{
	}

	void Update(MHelmet::DeltaTime dt) override 
	{
#if 0
			static int s_UpdateCount = 0;
			MH_INFO("TestingImGui::{0}", ++s_UpdateCount);	
#endif
		//if (MHelmet::Input::IsKeyPressed(MHelmet::Key::Space))	MH_TRACE("SPACE 1 is pressed");
		//if (MHelmet::Input::IsKeyPressed(MH_KEY_SPACE))     MH_TRACE("SPACE 2 is pressed");
		
	}

	void ImGuiRender()
	{
		/*ImGui::Begin("hola");
		ImGui::Text("caracola");
		ImGui::End();*/
	}



	void OnEvent(MHelmet::Event& event) override
	{
		// FILTRADO DE EVENTOS
		//if (event.GetEventType() == MHelmet::EventType::E_KEY_PRESSED)
		//{
		//	// sabiendo que es KEY_PRESSED 
		//	// guardamos como tal usando un alias
		//	// ya que el event pasado como paramentro
		//	// no tiene esa informacion
		//	MHelmet::OnKeyPressed& e = (MHelmet::OnKeyPressed&)event;

		//	if (e.GetKeyCode() == MH_KEY_SPACE)
		//	{
		//		
		//	}
		//
		//	MH_ERROR(static_cast<char>(e.GetKeyCode()));
		//}
	}
};
/**************************************
*           Proyecto Cliente          *
* *************************************/
class ProjectTesting : public MHelmet::Engine {

public:
	ProjectTesting()
	{
		PushLayer(new TestingLayer());
		//PushOverlay(new MHelmet::ImGuiLayer());
	}

	~ProjectTesting()
	{
	}
};

extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp()
{
	return std::make_unique<ProjectTesting>();
}

int main(int argc, char** argv)
{
	

	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();



	return 0;
}