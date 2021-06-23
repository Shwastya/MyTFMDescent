#include "MyTFM.hpp"

int main(int argc, char** argv)
{
	CORE::Init();

	auto project = createApp();
	project->run();

	CORE::Stop();

	return 0;
}

