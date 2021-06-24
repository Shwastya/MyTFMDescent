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
			
			/*auto& rotat = ent.GetComponent<TransformComponent>().R;
			auto& scale = ent.GetComponent<TransformComponent>().S;
			ImGui::DragFloat3("Rotate", glm::value_ptr(rotat), 0.25f);		
			ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);*/
			//ImGui::DragFloat("Degrees", (degrees), 0.1f);			
		}
		if (ent.HasComponent<CameraManComponent>())
		{
			
			if (ImGui::TreeNodeEx((void*)typeid(CameraManComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				
				float fov = ent.GetComponent<CameraManComponent>().Cameraman.Get().GetFOV();
				static float FOV = 0.0f;
				if (ImGui::DragFloat("Fov", &fov));
				{
					if (fov >= 0.1f && fov <= 100.0f) FOV = fov;
					if (fov <= 0.1f) FOV = 0.1f;
					if (fov >= 140.0f) FOV = 140.0f;
					ent.GetComponent<CameraManComponent>().Cameraman.SetFOV(FOV);
				}
			

				auto& Near = ent.GetComponent<CameraManComponent>().Near;
				if (ImGui::DragFloat("Near", &Near));
				ent.GetComponent<CameraManComponent>().Near = Near;

				auto& Far = ent.GetComponent<CameraManComponent>().Far;
				if (ImGui::DragFloat("Far", &Far));
				ent.GetComponent<CameraManComponent>().Far = Far;
				//ImGui::DragFloat3("Translate", glm::value_ptr(trans), 0.25f);

				ImGui::TreePop();
			}
		}
		if (ent.HasComponent<MaterialComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(MaterialComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Material Basic Phong"))
			{
				auto& ambient = ent.GetComponent<MaterialComponent>().Ambient;
				ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));
				

				auto& difusse = ent.GetComponent<MaterialComponent>().Difusse;
				ImGui::ColorEdit3("Difusse", glm::value_ptr(difusse));
				

				auto& specular = ent.GetComponent<MaterialComponent>().Specular;
				ImGui::ColorEdit3("Specular", glm::value_ptr(specular));
			

				auto& Shininess = ent.GetComponent<MaterialComponent>().Shininess;
				if (ImGui::DragInt("Shininess", &Shininess));
				ent.GetComponent<MaterialComponent>().Shininess = Shininess;

				ImGui::TreePop();
			}


		}
		
	}
}