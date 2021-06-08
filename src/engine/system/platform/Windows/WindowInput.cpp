#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Windows/WindowInput.hpp"
#include "engine/system/platform/Windows/WindowWin.hpp"
#include "engine/Engine.hpp";
#include <GLFW/glfw3.h> // siempre dentro de la plataforma CPP especifica

#define ENGINE_WIN  static_cast<WindowWin&>(Engine::p().GetWindow()) // void* ptr
#define NATIVE_WIN  static_cast<GLFWwindow*>

namespace MHelmet 
{
	// Como input es totalmente estatico, no tiene datos/atributos
	// no usa constructor/inicializador
	// podemos sin miedo hacer un allocate e instanciar
	// el singleton Input con una instancia de WindowInput

	Input* Input::s_Inst = new WindowInput();

	bool WindowInput::IsKeyPressed(KeyCode keycode)
	{
		// obtenemos el puntero a window especifico desde Engine global
		// que tiene el atributo GLFW window 
		// de las clases derrivadas de Window.hpp (no global)
		// asegurando que sea una instancia de WindowWin
		// ya que este input tiene que ser especifico para windows

		WindowWin& w = ENGINE_WIN;

		int K = glfwGetKey // get key state
		(
			NATIVE_WIN(w.GetOriginalWindow()),
			static_cast<int32_t>(keycode)
		); 

		return (K == GLFW_PRESS || K == GLFW_REPEAT);
	}
	bool WindowInput::IsMouseButtonPressed(MouseButton button)
	{
		WindowWin& w = ENGINE_WIN;

		int b = glfwGetMouseButton // get button mouse state
		(
			NATIVE_WIN(w.GetOriginalWindow()), 
			static_cast<int32_t>(button)
		);

		return (b == GLFW_PRESS);
	}
	
	float WindowInput::GetMouseX()
	{
		WindowWin& w = ENGINE_WIN;
		double x, y;

		glfwGetCursorPos // get mouse cursor position
		(
			NATIVE_WIN(w.GetOriginalWindow()),
			&x, &y
		); 

		return static_cast<float>(x);
	}

	float WindowInput::GetMouseY()
	{
		WindowWin& w = ENGINE_WIN;
		double x, y;
		glfwGetCursorPos // get mouse cursor position
		(
			NATIVE_WIN(w.GetOriginalWindow()),
			&x, &y
		); 

		return static_cast<float>(y);
	}

	MousePosition WindowInput::GetMousePos()
	{
		return 
		{ 
			// Averiguar si el hecho de si llamar a dos funciones
			// para resolver este caso es una perdidad de eficacia

			WindowInput::GetMouseX(), // get mouse cursor position X
			WindowInput::GetMouseY()  // get mouse cursor position Y
		};
	}	
}
