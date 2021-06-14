#include <MHelmet.h>






/**************************************
*       Proyecto Cliente Layer        *
* *************************************/
class ExampleLayer : public MHelmet::NodeLayer
{
public:
	ExampleLayer() : MHelmet::NodeLayer("EditorLayer")
	{
	}

	void Update(MHelmet::DeltaTime dt) override
	{
#if 1
		static int s_UpdateCount = 0;
		MH_INFO("ExampleLayer::{0}", ++s_UpdateCount);
#endif
	}
	void OnEvent(MHelmet::Event& event) override
	{
		MH_INFO("{0}", event);
	}
};
/**************************************
*           Proyecto Cliente          *
* *************************************/
class ProjectExample : public MHelmet::Engine {

public:
	ProjectExample()
	{
		PushLayer(new ExampleLayer());
	}

	~ProjectExample()
	{
	}
};


extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp()
{
	MH_INFO("Created Application: {}", "ProjectExample!");
	return std::make_unique<ProjectExample>();
}
//extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp();

int main(int argc, char** argv)
{

	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();



	return 0;
}