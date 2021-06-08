#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Windows/WindowInput.hpp"

#include "engine/Engine.hpp";
#include <GLFW/glfw3.h> // siempre dentro de la plataforma CPP especifica

#define NativeWindow  static_cast<GLFWwindow*>(Engine::p().GetWindow().GetOriginalWindow())

namespace MHelmet 
{
	// Como input es totalmente estatico, no tiene datos/atributos
	// no usa constructor/inicializador
	// podemos sin miedo hacer un allocate e instanciar
	// el singleton Input con una instancia de WindowInput

	Input* Input::s_Inst = new WindowInput();

	bool WindowInput::IsKeyPressedImpl(int keycode)
	{
		// obtenemos el puntero a window especifivo desde Engine global
		// que tiene la propiedad window (no global)
		auto w = NativeWindow; // void* ptr
		auto s = glfwGetKey(w, keycode); // state

		return (s == GLFW_PRESS || s == GLFW_REPEAT);
	}
	bool WindowInput::IsMouseButtonPressedImpl(int button)
	{
		auto w = NativeWindow; // void* ptr
		auto s = glfwGetMouseButton(w, button); // state

		return (s == GLFW_PRESS);
		//return false;
	}
	
	float WindowInput::GetMouseXImpl()
	{
		auto w = NativeWindow; // void* ptr
		double X_pos, Y_pos;
		glfwGetCursorPos(w, &X_pos, &Y_pos); // state

		return (float)X_pos;
	}

	float WindowInput::GetMouseYImpl()
	{
		auto w = NativeWindow; // void* ptr
		double X_pos, Y_pos;
		glfwGetCursorPos(w, &X_pos, &Y_pos); // state

		return (float)Y_pos;
	}

	MousePos WindowInput::GetMousePosImpl()
	{
		return 
		{ 
			WindowInput::GetMouseXImpl(), 
			WindowInput::GetMouseYImpl() 
		};
	}	
}
