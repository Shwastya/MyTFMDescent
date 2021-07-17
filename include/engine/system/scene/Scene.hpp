#pragma once
#include "entt.hpp"
#include "engine/system/utils/utils.hpp"


namespace MHelmet
{
	class Entity;
	class FrameBuffer;
	struct CameraFirstPerson;
	class Scene
	{
	public:
		Scene() = default;
		~Scene();

		Entity CreateEntity(const std::string& name = "unnamed");
		void DestroyEntity(Entity entity); 

		void UpdateFirstPersonCamera(TimeStep dt, const CameraFirstPerson& cam);
		void UpdateScreenTexture(const RefCount<FrameBuffer>& fbotexture);
		void Update(TimeStep dt);


		//void SetMode(bool mode);

	private:

		 entt::registry m_Registry;

		 friend class Entity;
		 friend class SceneHierarchyUI;
		 friend class SerializerScene;
	};
}