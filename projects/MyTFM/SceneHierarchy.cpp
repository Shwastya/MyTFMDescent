#include "SceneHierarchy.hpp"
//#include <imgui.h>

namespace MHelmet
{
	SceneHierarchy::SceneHierarchy(const RefCount<Scene>& context)
	{
		SetContext(context);
	}
	void SceneHierarchy::SetContext(const RefCount<Scene>& context)
	{
		m_Context = context;
	}
	void SceneHierarchy::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");

		m_Context->m_Registry.each([&](auto entity)
		{
		//		DrawEntityNode(entity);

			auto& t = m_Context->m_Registry.get<TagComponent>(entity);
			ImGui::Text("%s", t.Tag.c_str());
		});

		

		ImGui::End();
	}
	void SceneHierarchy::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		//ImGui::TreeNodeEx((void*)(uin32_t));
	}
}