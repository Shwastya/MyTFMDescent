#include "ProjectExample.hpp"

int main(int argc, char** argv)
{
	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();

	return 0;
}

