#pragma once
#include "entt.hpp"
#include "engine/system/utils/utils.hpp"


namespace MHelmet
{
	class Entity;
	class CameraFirstPerson;
	class Scene
	{
	public:
		Scene() = default;
		~Scene();

		Entity CreateEntity(const std::string& name = "unnamed");
		void DestroyEntity(Entity entity); 

		void UpdateEditorCamera(DeltaTime dt, const CameraFirstPerson& cam);
		void Update(DeltaTime dt);

	private:

		 entt::registry m_Registry;

		 friend class Entity;
		 friend class SceneHierarchy;
		 friend class SerializerScene;
	};
}