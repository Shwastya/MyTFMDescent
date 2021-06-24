#include "SceneHierarchy.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui_internal.h>

namespace MHelmet
{
	static void DrawVec3(const std::string& label, glm::vec3& values, float reset = 0.0f, float columnWidth = 100.0f)
	{

		ImGui::PushID(label.c_str()); // cada Vec3 control tiene un unico label
		{
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize)) values.x = reset;
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize)) values.y = reset;
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize)) values.z = reset;
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
		//	ImGui::SameLine();
			ImGui::PopStyleVar(); // final pop var
			ImGui::Columns(1);
		}
		ImGui::PopID();
	}

	SceneHierarchy::SceneHierarchy(const RefCount<Scene>& context) { SetContext(context); }

	void SceneHierarchy::SetContext(const RefCount<Scene>& context)	{ m_Context = context;}





	void SceneHierarchy::OnImGuiRender()
	{
		
		ImGui::Begin("Hierarchy");
		
		m_Context->m_Registry.each([&](auto IDentity)
		{
			//Entity  = m_Context->m_Registry.get<TagComponent>(entity);
			Entity entity{ IDentity, m_Context.get() };
			DrawNodes(entity);
			//ImGui::Text("%s", t.Tag.c_str());
		});
				
		//ImGui::End();

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) // click derecho en blank space
		{
			m_CollectionContext = {};
			//WARN("CLICLK");
		}

		
		if (ImGui::BeginPopupContextWindow(0, 1, false)) // TRIGGER al anyadir un item
		{
			if (ImGui::MenuItem("Create Empty Entity")) 
				m_Context->CreateEntity("Empty Entity");
			ImGui::EndPopup();

		}
		ImGui::End();

		ImGui::Begin("Properties");		
		if (m_CollectionContext) 
			DrawComponents(m_CollectionContext);
		
		ImGui::End();
	}





	void SceneHierarchy::DrawNodes(Entity ent)
	{
		auto& tag = ent.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_CollectionContext == ent) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		
		// 64_t para puntero void en sistemas x64
		//bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)ent, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_CollectionContext = ent;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem()) 
		{
			if (ImGui::MenuItem("Delete Entity")) 
				 entityDeleted = true;
			ImGui::EndPopup();
		}		
		
		if (opened)
		{
			//srand(time(NULL)); // one more hack // hash number
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			// intenta acceder al tag, si se ha destruido no existe
			bool opened = ImGui::TreeNodeEx((void*)978657, flags, tag.c_str()); 
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		} 

		if (entityDeleted)
		{
			m_Context->DestroyEntity(ent);
			if (m_CollectionContext == ent)
				m_CollectionContext = {};
		}
		
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
				auto& TC = ent.GetComponent<TransformComponent>();
				DrawVec3("Translation", TC.T);
				glm::vec3 rotation = glm::degrees(TC.R);
				DrawVec3("Rotation", rotation);
				TC.R = glm::radians(rotation);
				DrawVec3("Scale", TC.S, 1.0f);
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