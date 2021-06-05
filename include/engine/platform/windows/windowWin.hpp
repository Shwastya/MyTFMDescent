#pragma once

#include "engine/platform/Window.hpp"
#include <GLFW/glfw3.h>


namespace MHelmet {

	class WindowWin : public Window 
	{


		struct WindowData
		{
			const char* Title;
			UI_Vec	    Size;
			bool        VSync;
		};

	public:
		WindowWin(const WindowSpec& spec);
		virtual ~WindowWin();

		virtual void Init() override;		
		virtual void SwapBuffers() override;

		inline uint32_t GetWidth()  const override { return m_Data.Size.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Size.Height; }

		virtual UI_Vec	 GetSize()  const override { return  m_Data.Size; }
		virtual FL_Vec	 GetPos()   const override;

		virtual void Maximize() override;

		virtual void SetVSync(bool toggle) override;
		virtual bool IsVSync() const override;
	private:
		void ShutDown();

	private:
		GLFWwindow* m_Window;
		WindowSpec  m_Spec;

		WindowData m_Data;
		float m_LastFrame = 0.0f;		


	};

}