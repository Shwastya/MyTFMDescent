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

	void Update() override
	{
#if 0
		static int s_UpdateCount = 0;
		MH_INFO("TestingLayer::{0}", ++s_UpdateCount);
#endif

		if (MHelmet::Input::IsKeyPressed(MHelmet::Key::Space))
			MH_TRACE("SPACE 1 is pressed");
		if (MHelmet::Input::IsKeyPressed(MH_KEY_SPACE))
		{
			MH_TRACE("SPACE 2 is pressed");
		}
	}
	void OnEvent(MHelmet::Event& event) override
	{
		//MH_INFO("{0}", event);
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

		// MHelmet::ImGuiLayer* temp(MHelmet::ImGuiLayer());

		//PushOverlay(new MHelmet::ImGuiLayer());

		PushOverlay(new MHelmet::ImGuiLayer());
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