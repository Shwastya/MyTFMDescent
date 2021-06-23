#include "MyTFMLayer1.hpp"

class MyTFM : public MHelmet::Engine 
{

public:

	MyTFM() : MHelmet::Engine("MyTFMDescent")
	{
		PushLayer(new MyTFMDescent());
	}

	~MyTFM() { /* delete de layers responsabilidad del Engine */ }
};


 Unique<Engine> createApp() 
{ 
	return std::make_unique<MyTFM>(); 
}