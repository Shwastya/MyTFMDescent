#pragma once
#include <MHelmet.h>

/**************************************
*  main() punto de entrada proyectos  *
* *************************************/
extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp();

int main(int argc, char** argv )
{	
	
	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();
	

	
	return 0;
}