#pragma once
#include <MHelmet.h>

/**************************************
*  main() punto de entrada proyectos  *
* *************************************/

extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp();

int main(int argc, char** argv )
{	
	MHelmet::Log::Init();
	MHelmet::Log::GetCoreLogger()->warn("Initialized Log System!");
	MHelmet::Log::GetClientLogger()->info("[EntryPoint]-> calls create application");
	//std::cout << "estoy en main point y creo la aplicacion" << std::endl;
	auto project = MHelmet:: createApp();
	project->run();	

	return 0;
}