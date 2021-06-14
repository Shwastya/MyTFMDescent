#pragma once

#include "engine/system/platform/Window.hpp"

#include "engine/system/renderer/RendererContext.hpp"





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
		virtual void Update() override; // updating

		virtual void Maximize() override;

		inline uint32_t GetWidth()  const override { return m_Data.Size.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Size.Height; }

		inline virtual Size_Vec GetSize()  const override { return  m_Data.Size; }
		virtual Pos_Vec GetPos() const override;

		inline virtual void* GetOriginalWindow() const override { return m_Window;  };


		inline virtual void SetCallBack(const CALLBACK& cb) override
		{
			m_Data.CallBack = cb;
		}

		virtual void SetVSync(bool toggle) override;
		inline virtual bool IsVSync() const override { return m_Data.VSync; };

		/******* TEMPORAL *******/
		virtual float GetDeltaTime() const override { return m_DeltaTime;  }
		/************************/

	private:
		void ShutDown();

	private:
		GLFWwindow* m_Window;
		WindowSpec  m_Spec;
		
		WindowData m_Data;
		float m_LastFrame = 0.0f;	

		/******* TEMPORAL *******/
		float m_DeltaTime = 18.0f;
		/************************/

		
		RendererContext* m_Context;
	};

}