#pragma once
#include "entt.hpp"


namespace MHelmet
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;


	};
}