#pragma once

#include "engine/platform/Window.hpp"
#include <GLFW/glfw3.h>


namespace MHelmet {

	class WindowWin : public Window 
	{
		struct WindowData
		{
			std::string Title;
			Size_Vec	Size;
			bool        VSync;

			// Event System CallBacks
			CALLBACK CallBack;
		};

	public:
		WindowWin(const WindowSpec& spec);
		virtual ~WindowWin();

		virtual void Init() override;		
		virtual void SwapBuffers() override; // updating

		virtual void Maximize() override;

		inline uint32_t GetWidth()  const override { return m_Data.Size.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Size.Height; }

		inline virtual Size_Vec GetSize()  const override { return  m_Data.Size; }
		virtual Pos_Vec GetPos() const override;

		inline virtual void* GetWindow() const override { return m_Window;  };


		inline virtual void SetCallBack(const CALLBACK& cb) override
		{
			m_Data.CallBack = cb;
		}

		virtual void SetVSync(bool toggle) override;
		inline virtual bool IsVSync() const override { return m_Data.VSync; };

	private:
		void ShutDown();

	private:
		GLFWwindow* m_Window;
		WindowSpec  m_Spec;
		
		WindowData m_Data;
		float m_LastFrame = 0.0f;	
	};

}