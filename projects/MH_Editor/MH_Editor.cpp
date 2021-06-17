#include "../src/engine/MHelmetPch.cpp"
/**************************************
*       Proyecto Cliente Layer        *
* *************************************/
class EditorLayer : public MHelmet::NodeLayer
{
public:
	EditorLayer() : NodeLayer("EditorLayer")
	{

	}

	void Update(MHelmet::DeltaTime dt) override
	{
#if 0
		INFO("EditorLayer::{0}", "Update");
#endif
	}
	void OnEvent(MHelmet::Event& event) override
	{
		TRACE("{0}", event);
	}

};
/**************************************
*           Proyecto Cliente          *
* *************************************/
class Editor : public MHelmet::Engine {

public:

	Editor() 
	{
		PushLayer(new EditorLayer());
	
	}
	
	~Editor() 
	{
	
	
	}
};

extern MHelmet::Unique<MHelmet::Engine> MHelmet::createApp() 
{	
	INFO("Created Application: {}", "Engine!");

	return std::make_unique<Editor>();
}

int main(int argc, char** argv)
{

	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();



	return 0;
}
