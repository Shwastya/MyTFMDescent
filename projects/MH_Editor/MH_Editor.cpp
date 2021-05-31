
#include <MHelmet.h>

/**************************************
*           Proyecto Cliente          *
* *************************************/

class Editor : public MHelmet::Engine {

public:

	Editor() {}
	~Editor() {}
};

std::unique_ptr<MHelmet::Engine> MHelmet::createApp() 
{
	const char* name = "Editor";
	//MHelmet::Log::GetClientLogger()->info("[Project]-> Return pointer Editor app'");
	MH_CLIENT_INFO("Created and running! App={0}", name);

	return std::make_unique<Editor>();
}
