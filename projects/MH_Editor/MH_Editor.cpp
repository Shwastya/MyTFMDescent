
#include <MHelmet.h>

/**************************************
*           Proyecto Cliente          *
* *************************************/

class Editor : public MHelmet::Engine {

public:

	Editor() {}
	~Editor() {}

	inline std::string getName(const std::string name) const { return m_ProjectName; };

private:
	std::string m_ProjectName = "Editor";
};

std::unique_ptr<MHelmet::Engine> MHelmet::createApp() 
{

	
	MH_INFO("Created Application: {}", "Engine!");

	return std::make_unique<Editor>();
}
