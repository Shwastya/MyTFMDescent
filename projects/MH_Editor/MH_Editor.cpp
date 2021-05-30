
#include <MHelmet.h>

/**************************************
*           Proyecto Cliente          *
* *************************************/

class Editor : public MHelmet::Engine {

public:

	Editor() {}
	~Editor() {}
};

/// Prototipo en Engine dentro del namespace
/// Enviado al Entry Point (main principal)
std::unique_ptr<MHelmet::Engine> MHelmet::createApp() 
{
	
	std::cout << "retorno proyecto a mainPoint" << std::endl;

	return std::make_unique<Editor>();
}
