#include "MyTFMLayer1.hpp"

class MyTFM : public MHelmet::Engine 
{

public:

	MyTFM() : MHelmet::Engine("MyTFMDescent")
	{
		PushLayer(new MyTFMDescent());
	}

	~MyTFM() = default;
};


 Unique<Engine> createApp() 
{ 
	return std::make_unique<MyTFM>(); 
}