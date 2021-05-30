//#include "../../include/engine/engine.hpp"


#include <MHelmet.h>

/**************************************
*           Proyecto Cliente          *
* *************************************/

class MiProyecto : public MHelmet::Engine {

public:

	MiProyecto() {}
	~MiProyecto() {}
};


//MHelmet::Engine* buildApp()
//{
//	return new MiProyecto();
//}




//MHelmet::Engine* MHelmet::createApp()
//{
//	return new MiProyecto();
//}

std::unique_ptr<MHelmet::Engine> MHelmet::createApp()
{
	//std::unique_ptr<MHelmet::Engine> e = std::make_unique<MiProyecto>();
	std::cout << "retorno proyecto a mainPoint" << std::endl;
	return std::make_unique<MiProyecto>();
}
//buildApp()