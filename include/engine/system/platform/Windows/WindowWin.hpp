#pragma once

#include "engine/system/platform/Window.hpp"
#include "engine/system/renderer/RendererContext.hpp"






namespace MHelmet {

	class WindowWin : public Window 
	{
		struct WindowData
		{
			std::string Title;
			Size	    Size;
			bool        VSync;

			// Event System CallBacks from GLFWwindow* callbacks lambda functions
			std::function<void(Event&)> CallBack;
		};

	public:
		WindowWin(const WindowSpec& spec);
		virtual ~WindowWin();

		virtual void Init() override;		
		virtual void SwapBuffers() override; // updating

		virtual void Maximize() override;

		inline uint32_t GetWidth()  const override { return m_Data.Size.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Size.Height; }

		inline virtual Size GetSize()  const override { return  m_Data.Size; }
		virtual Position GetPos() const override;

		inline virtual void* GetOriginalWindow() const override { return m_Window;  };


		inline virtual void SetCallBack(const std::function<void(Event&)>& cb) override
		{
			m_Data.CallBack = cb;
		}

		virtual void SetVSync(bool toggle) override;
		inline virtual bool IsVSync() const override { return m_Data.VSync; };	

		/******* TEMPORAL *******/
		virtual void SetCaptureMode(bool toggle) const override;

	private:
		void ShutDown();

	private:
		GLFWwindow* m_Window;

		WindowSpec  m_Spec;		
		WindowData  m_Data;
		
		RendererContext* m_Context;
	};

}