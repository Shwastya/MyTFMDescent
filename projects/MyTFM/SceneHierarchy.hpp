#pragma once
#include <MHelmet.h>


namespace MHelmet
{
	class SceneHierarchy
	{
	public:

		SceneHierarchy() = default;
		SceneHierarchy(const RefCount<Scene>& context);

		void SetContext(const RefCount<Scene>& context);

		void OnImGuiRender();

	private:
		void DrawNodes(Entity entity);
		void DrawComponents(Entity entity);

	private:
		RefCount<Scene> m_Context;
		Entity m_CollectionContext;
		//bool m_PrimaryCam = true;

	};
}