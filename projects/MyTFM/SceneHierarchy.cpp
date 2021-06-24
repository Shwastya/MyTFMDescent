#include "SceneHierarchy.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace MHelmet
{
	SceneHierarchy::SceneHierarchy(const RefCount<Scene>& context) { SetContext(context); }

	void SceneHierarchy::SetContext(const RefCount<Scene>& context)	{ m_Context = context;}





	void SceneHierarchy::OnImGuiRender()
	{
		
		ImGui::Begin("Hierarchy");
		{
			m_Context->m_Registry.each([&](auto IDentity)
			{
				//Entity  = m_Context->m_Registry.get<TagComponent>(entity);
				Entity entity{ IDentity, m_Context.get() };
				DrawNodes(entity);
				//ImGui::Text("%s", t.Tag.c_str());
			});
		}		
		ImGui::End();

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered)
		{

		}


		ImGui::Begin("Properties");
		{
			if (m_CollectionContext) DrawComponents(m_CollectionContext);
		}
		ImGui::End();
	}





	void SceneHierarchy::DrawNodes(Entity ent)
	{
		auto& tag = ent.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_CollectionContext == ent) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		
		// 64_t para puntero void en sistemas x64
		//bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)ent, flags, tag.c_str());
		
		if (ImGui::IsItemClicked()) m_CollectionContext = ent;
		
		if (opened) ImGui::TreePop();
		
	}
	void SceneHierarchy::DrawComponents(Entity ent)
	{
		auto& tag = ent.GetComponent<TagComponent>().Tag;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("Label", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer);
		}


		if (ent.HasComponent<TransformComponent>())
		{

			// collapsa paneles y ayuda a organizarlo un poco mejor
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& trans = ent.GetComponent<TransformComponent>().T;
				ImGui::DragFloat3("Translate", glm::value_ptr(trans), 0.25f);

				ImGui::TreePop();
			}
			
			auto& rotat = ent.GetComponent<TransformComponent>().R;
			auto& scale = ent.GetComponent<TransformComponent>().S;
			ImGui::DragFloat3("Rotate", glm::value_ptr(rotat), 0.25f);		
			ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);

			//ImGui::DragFloat("Degrees", (degrees), 0.1f);
			
			
		}
	}
}