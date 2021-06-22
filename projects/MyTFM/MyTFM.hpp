#include "MyTFMLayer1.hpp"

class MyTFM : public MH::Engine 
{

public:

	MyTFM() : MH::Engine("MyTFMDescent")
	{
		PushLayer(new MyTFMDescent());
	}

	~MyTFM() { /* delete de layers responsabilidad del Engine */ }
};


extern MH::Unique<MH::Engine> MH::createApp() 
{ 
	return std::make_unique<MyTFM>(); 
}