#pragma once
#include <MHelmet.h>

/**************************************
*  main() punto de entrada proyectos  *
* *************************************/

extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp();

int main(int argc, char** argv )
{	
	std::cout << "estoy en main point y creo la aplicacion" << std::endl;
	auto project = MHelmet:: createApp();
	project->run();	

	return 0;
}