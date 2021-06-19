#include "MyTFMLayer1.hpp"

class MyTFM : public MHelmet::Engine 
{

public:

	MyTFM()
	{
		PushLayer(new MyTFMDescent());
	}

	~MyTFM() { /* delete de layers responsabiliad del Engine */ }
};


MH::Unique<MH::Engine> MH::createApp() 
{ 
	return std::make_unique<MyTFM>(); 
}