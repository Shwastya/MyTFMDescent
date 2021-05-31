
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
	//MHelmet::Log::GetClientLogger()->info("[Project]-> Return pointer Editor app'");

	return std::make_unique<Editor>();
}
