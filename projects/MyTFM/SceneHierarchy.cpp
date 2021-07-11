#include "SceneHierarchy.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui_internal.h>
#include "engine/system/scene/Components.hpp"

namespace MHelmet
{
	template<typename T, typename UIFunc>
	static void DrawComponent(const std::string& name, Entity ent, UIFunc UIfunction) 
	{
		const ImGuiTreeNodeFlags treenodeFlags = 
			ImGuiTreeNodeFlags_DefaultOpen      | 
			ImGuiTreeNodeFlags_Framed           | 
			ImGuiTreeNodeFlags_SpanAvailWidth   | 
			ImGuiTreeNodeFlags_AllowItemOverlap | 
			ImGuiTreeNodeFlags_FramePadding;

		if (ent.HasComponent<T>())
		{
			auto& component = ent.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 2, 2 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treenodeFlags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("-", ImVec2{ lineHeight, lineHeight}))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			//ImGui::PopStyleVar();

			bool remove = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component")) remove = true;
			
				ImGui::EndPopup();
			}

			if (open)
			{
				UIfunction(component);
				ImGui::TreePop();
			}
			if (remove) ent.RemoveComponent<T>();
		}
	}
	static void DrawVec3(const std::string& label, glm::vec3& values, float reset = 0.0f, float columnWidth = 100.0f)
	{

		ImGuiIO& io = ImGui::GetIO();
		auto BoldFont = io.Fonts->Fonts[0];

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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.6f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("X", buttonSize)) values.x = reset;
			ImGui::PopFont();


			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.4f, 0.6f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.7f, 0.2f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("Y", buttonSize)) values.y = reset;
			ImGui::PopFont();

			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });

			ImGui::PushFont(BoldFont);
			if (ImGui::Button("Z", buttonSize)) values.z = reset;
			ImGui::PopFont();

			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::PopStyleVar(); // final pop var
			ImGui::Columns(1);
		}
		ImGui::PopID();
	}

	void SceneHierarchy::SetContext(const RefCount<Scene>& context)	{ m_Context = context;}

	void SceneHierarchy::OnImGuiRender()
	{		
		ImGui::Begin("Hierarchy");
		
		m_Context->m_Registry.each([&](auto IDentity)
		{
			Entity entity{ IDentity, m_Context.get() };
			DrawNodes(entity);			
		});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) // click derecho en blank space
		{
			m_CollectionContext = {};
		}

		// al pulsat boton emerge menu
		if (ImGui::BeginPopupContextWindow(0, 1, false)) // TRIGGER al anyadir un item
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				m_Context->CreateEntity("Empty Entity");				
			}
				
			ImGui::EndPopup();
		}
		ImGui::End();

		ImGui::Begin("Properties");		
		//ImGui::NewLine();
		if (m_CollectionContext)
		{
			DrawComponents(m_CollectionContext);			
		}

		ImGui::End();

		ImGui::Begin("Assets Store");
		
		if (m_CollectionContext)
		{
			AssetStore();
		}
		ImGui::End();

		ImGui::Begin("Log Info");
		//ImGui::NewLine();
		ImGui::Text("  Last log message:");
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::Text(m_Log.c_str());
		ImGui::PopStyleColor();
		
		ImGui::End();
	}

	void SceneHierarchy::DrawNodes(Entity ent)
	{
		auto& tag = ent.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_CollectionContext == ent) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		// 64_t para puntero void en sistemas x64
		//bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)ent, flags, tag.c_str());
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
			srand(time(NULL));
			bool opened = ImGui::TreeNodeEx((void*)rand(), flags, tag.c_str()); 
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		} 

		if (entityDeleted)
		{
			/*if (ent.HasComponent<CameraComponent>())
			{
				m_Log = "Cameras cannot be deleted yet.....";
			}*/
				
		
			//else
			{
				m_Context->DestroyEntity(ent);
				if (m_CollectionContext == ent)
					m_CollectionContext = {};
			}			
		}		
	}

	// DRAWING COMPONENTS
	void SceneHierarchy::DrawComponents(Entity ent)
	{
		auto& tag = ent.GetComponent<TagComponent>().Tag;

		// DIBUJADO DE LABEL componente
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		//ImGui::NewLine();
		if (ImGui::InputText("##Label", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer); 
		}
		//ImGui::NewLine();
		//const ImGuiTreeNodeFlags treenodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);


		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponent"); // AddComponent ID 
		}

		if (ImGui::BeginPopup("AddComponent")) // if ID button
		{

			ImGui::Indent();
			if (ImGui::MenuItem("Material"))
			{

				if (m_CollectionContext.HasComponent<MaterialComponent>())
				{
					m_Log = "The entity already has material";
					WARN("{0}", m_Log);
				}
				/*else if (m_CollectionContext.HasComponent<CameraComponent>())
				{
					m_Log = "The camera cannot have a material component!";
					WARN("{0}", m_Log);
				}*/
				else
				{
					if (m_CollectionContext.HasComponent<TextureComponent>())
					{
						m_CollectionContext.RemoveComponent<TextureComponent>();
					}

					m_CollectionContext.AddComponent<MaterialComponent>();

					//m_CollectionContext.

					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::NewLine();
			if (ImGui::MenuItem("Texture"))
			{
				if (m_CollectionContext.HasComponent<TextureComponent>())
				{
					m_Log = "The entity already has texture";
					WARN("{0}", m_Log);
				}
				/*else if (m_CollectionContext.HasComponent<CameraComponent>())
				{
					m_Log = "The camera cannot have a texture component!";
					WARN("{0}", m_Log);
				}*/
				else
				{
					if (m_CollectionContext.HasComponent<MaterialComponent>())
					{
						m_CollectionContext.RemoveComponent<MaterialComponent>();
					}

					m_CollectionContext.AddComponent<TextureComponent>(Texture2D::Format::RGB);
					m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::NewLine();
			if (ImGui::MenuItem("Point Light"))
			{
				if (m_CollectionContext.HasComponent<PointLightComponent>())
				{
					m_Log = "The entity already has a Point Light";
					WARN("{0}", m_Log);
				}
			/*	else if (m_CollectionContext.HasComponent<CameraComponent>())
				{
					m_Log = "The camera cannot have a Point LiGHT!";
					WARN("{0}", m_Log);
				}*/
				else if (m_CollectionContext.HasComponent<LightComponent>())
				{
					m_Log = "The Directional Light cannot have a Point LiGHT!";
					WARN("{0}", m_Log);
				}
				else
				{
					m_CollectionContext.AddComponent<PointLightComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::Unindent();
			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();


		DrawComponent<TransformComponent>("Transform", ent, [](auto& component)
		{				
			DrawVec3("Translation", component.T);
			glm::vec3 rotation = glm::degrees(component.R);
			DrawVec3("Rotation", rotation);
			component.R = glm::radians(rotation);
			DrawVec3("Scale", component.S, 1.0f);
		});
		
	/*	DrawComponent<CameraComponent>("Camera", ent, [](auto& component)
		{
				
			float& fov = component.Camera.FOV();
	
			if (ImGui::DragFloat("Fov", &fov));
			{
				if (fov >= 0.1f && fov <= 100.0f) fov = fov;
				if (fov <= 0.1f) fov = 0.1f;
				if (fov >= 140.0f) fov = 140.0f;				
			}				
			if (ImGui::DragFloat("Near", &component.Near));
			if (ImGui::DragFloat("Far", &component.Far));
		});*/

		DrawComponent<LightComponent>("Directional Light", ent, [](auto& component)
		{
			DrawVec3("Direction", component.Direction);
			DrawVec3("Position",  component.Position);
			ImGui::NewLine();
			ImGui::ColorEdit3("Ambient",  glm::value_ptr(component.Ambient));				
			ImGui::ColorEdit3("Difusse",  glm::value_ptr(component.Difusse));			
			ImGui::ColorEdit3("Specular", glm::value_ptr(component.Specular));			
		});
		
		DrawComponent<PointLightComponent>("Point Light", ent, [](auto& component)
		{				
			ImGui::ColorEdit3("Ambient",  glm::value_ptr(component.Ambient));
			ImGui::ColorEdit3("Difusse",  glm::value_ptr(component.Difusse));
			ImGui::ColorEdit3("Specular", glm::value_ptr(component.Specular));
			if (ImGui::DragFloat("Linear",    &component.Linear));
			if (ImGui::DragFloat("Quadratic", &component.Quadratic));
		});

		DrawComponent<SpotLightComponent>("Spot Light", ent, [](auto& component)
		{
			ImGui::ColorEdit3("Ambient",  glm::value_ptr(component.Ambient));
			ImGui::ColorEdit3("Difusse",  glm::value_ptr(component.Difusse));
			ImGui::ColorEdit3("Specular", glm::value_ptr(component.Specular));
			if (ImGui::DragFloat("Linear",      &component.Linear));		
			if (ImGui::DragFloat("Quadratic",   &component.Quadratic));		
			if (ImGui::DragFloat("outerCutOff", &component.OuterCutOff));				
		});		

		DrawComponent<MaterialComponent>("Material", ent, [](auto& component)
		{
			ImGui::ColorEdit3("Ambient",  glm::value_ptr(component.Ambient));
			ImGui::ColorEdit3("Difusse",  glm::value_ptr(component.Difusse));
			ImGui::ColorEdit3("Specular", glm::value_ptr(component.Specular));
			ImGui::DragInt("Shininess",   &component.Shininess);
		});

		DrawComponent<TextureComponent>("Texture", ent, [](auto& component) 
		{
			ImGui::DragInt("Shininess", &component.Shininess);
			ImGui::NewLine();
			ImGui::Text("Choose a texture for the selected entity:");
			ImGui::NewLine();

			if (ImGui::Button("Skulls", ImVec2{ 100, 20 }))
			{
				component.P_A = "../assets/textures/skull_low/Skulls_base.png";
				component.P_S = "../assets/textures/skull_low/Skulls_specular.png";
				component.P_N = "../assets/textures/skull_low/Skulls_normal.png";
				component.SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Broken", ImVec2{ 100, 20 }))
			{
				component.P_A = "../assets/textures/low_broken/BrokenLimestoneBrickPath_basecolor.png";
				component.P_S = "../assets/textures/low_broken/BrokenLimestoneBrickPath_height.png";
				component.P_N = "../assets/textures/low_broken/BrokenLimestoneBrickPath_normal.png";
				component.SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Brain", ImVec2{ 100, 20 }))
			{
				component.P_A = "../assets/textures/brain/Brain_Matter_001_COLOR.jpg";
				component.P_S = "../assets/textures/brain/Brain_Matter_001_SPEC.jpg";
				component.P_N = "../assets/textures/brain/Brain_Matter_001_NORM.jpg";
				component.SetComponentTexture();
			}
		});			
	}
	
	void SceneHierarchy::AssetStore()
	{		
		const bool hasTransform = m_CollectionContext.HasComponent<TransformComponent>();
		const bool isLightReference = m_CollectionContext.HasComponent<LightComponent>();

		if (isLightReference)
		{
			m_Log = "Triangle helps to know the direction of light";
		}

		if (hasTransform && (!isLightReference))
		{
			ImGui::NewLine();
			ImGui::Text("Choose an asset for the selected entity:");
			ImGui::NewLine();

			if (ImGui::Button("Triangle", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 3;
			}
			ImGui::SameLine();
			if (ImGui::Button("Quad", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 4;			
			}
			ImGui::SameLine();
			if (ImGui::Button("Cube", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 1;
			}
			ImGui::Separator();

			if (ImGui::Button("Sphere", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 5;
			}
			ImGui::SameLine();
			if (ImGui::Button("Tea Pot", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 2;
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TransformComponent>().ID = 0;
			}				
		}				
	}
}