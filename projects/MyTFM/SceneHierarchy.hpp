#pragma once
#include <MHelmet.h>


namespace MHelmet
{
	class SceneHierarchyUI
	{
	public:

		SceneHierarchyUI() = default;
		SceneHierarchyUI(const RefCount<Scene>& context) { SetContext(context); };

		void SetContext(const RefCount<Scene>& context);

		void ImGuiRender();

		Entity GetCollectedEntity() const { return m_CollectionContext; }

	private:
		void DrawNodes(Entity entity);
		void DrawComponents(Entity entity);	

		void AssetStore();

	private:
		RefCount<Scene> m_Context;
		Entity m_CollectionContext;

		std::string m_Log;
	};
}