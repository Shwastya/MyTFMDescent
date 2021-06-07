#include <MHelmet.h>
/**************************************
*       Proyecto Cliente Layer        *
* *************************************/
class EditorLayer : public MHelmet::NodeLayer
{
public:
	EditorLayer() : NodeLayer("EditorLayer")
	{

	}

	void Update() override
	{
#if 0
		MH_INFO("EditorLayer::{0}", "Update");
#endif
	}
	void OnEvent(MHelmet::Event& event) override
	{
		MH_TRACE("{0}", event);
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

std::unique_ptr<MHelmet::Engine> MHelmet::createApp() 
{	
	MH_INFO("Created Application: {}", "Engine!");

	return std::make_unique<Editor>();
}
