
#include "engine/engine.hpp"

#include "engine/events/AppEvents/OnAppEvents.hpp"
#include "engine/events/KeyEvents/OnKeyEvents.hpp"


#include <GLFW/glfw3.h>
#include <bitset>

namespace MHelmet 
{
	
	Engine::Engine()
	{
	
	}
	Engine::~Engine() {}	


	void Engine::run()
	{
		MH_ENGINE_INFO("Engine is running now!");
		
		OnWindowResize e(1280, 720);

		//e->(EventType::KeyPressed);
		
		MH_TRACE(e);

	/*	std::cout << (1 << 1) << std::endl;
		std::cout << (1 << 2) << std::endl;*/

		OnKeyPressed k1(MH_KEY_COMMA, 0);
		OnKeyPressed k2(MH_KEY_5, 1);

		MH_TRACE(k1);

		std::cout << "categoryFlag k1: " << k1.GetCategoryFlags() << std::endl;
		k1.IsInCategory(MHelmet::EventCategory::E_CATG_KEYBOARD);
		/*std::cout << "K1 Is_In_Category bool: " << 
			std::bitset<8>(k1.IsInCategory(MHelmet::EventCategory::EventCategoryKeyboard))
			<< std::endl;*/

		std::cout << "categoryFlag k2: " << k2.GetCategoryFlags() << std::endl;
		k2.IsInCategory(MHelmet::EventCategory::E_CATG_MOUSE);
		/*std::cout << "K2 Is_In_Category bool: " <<
			std::bitset<8>(k2.IsInCategory(MHelmet::EventCategory::EventCategoryMouse))
			<< std::endl;*/

		/*std::cout << "size in bytes of int     : " << sizeof(int) << std::endl;
		std::cout << "size in bytes of uint16_t: " << sizeof(uint16_t) << std::endl;*/


		// stride data bit a bit
		/*int16_t i = 1;
		int8_t* p = reinterpret_cast<int8_t*>(&i);*/



		/*if (p[0] == 1) printf("Little Endian\n");
		else           printf("Big Endian\n");*/

		
		while (m_Running)
		{
			
		}
	}	
}

