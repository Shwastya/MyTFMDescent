#pragma once

#include "PerspectiveCamera.hpp"

namespace MHelmet
{
	class Renderer3D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		// models

	};
}