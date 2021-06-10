#pragma once

namespace MHelmet
{

	class RendererContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
} 