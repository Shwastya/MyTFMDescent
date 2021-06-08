#include <MHelmet.h>
#include "engine/system/ImGui/ImGuiLayer.hpp"
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