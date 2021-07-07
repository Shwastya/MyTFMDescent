#include "SceneHierarchy.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui_internal.h>
#include "engine/system/scene/Components.hpp"

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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.6f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize)) values.x = reset;
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f"); // ## NO MUESTRA LABEL
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// colores de los botones
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.4f, 0.6f, 0.3f, 1.0f });
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
			ImGui::NewLine();
			ImGui::Separator();
			ImGui::NewLine();


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
					else if (m_CollectionContext.HasComponent<CameraManComponent>())
					{
						m_Log = "The camera cannot have a material component!";
						WARN("{0}", m_Log);
					}					
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
					else if (m_CollectionContext.HasComponent<CameraManComponent>())
					{
						m_Log = "The camera cannot have a texture component!";
						WARN("{0}", m_Log);
					}
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
				ImGui::Unindent();
				ImGui::EndPopup();		
			}
		}

		ImGui::End();

		ImGui::Begin("Directional Light");
		m_Context->m_Registry.each([&](auto IDentity)
		{
			Entity entity{ IDentity, m_Context.get() };
			if (entity.HasComponent<LightComponent>())
				DrawComponentLight(entity);
		});
	
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
			if (ent.HasComponent<CameraManComponent>())
			{
				m_Log = "Cameras cannot be deleted yet.....";
			}
				
		
			else
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
		ImGui::NewLine();
		if (ImGui::InputText("Label", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer); 
		}
		ImGui::NewLine();
		const ImGuiTreeNodeFlags treenodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;


		// DIBUJADO DE TRANSFORM componente
		const bool hasTransform = ent.HasComponent<TransformComponent>();
		
		if (hasTransform)
		{
			ImGui::Separator();
			ImGui::NewLine();
			bool open = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treenodeFlags, "Transform");	
			
			if (open)
			{
				
				auto& TC = ent.GetComponent<TransformComponent>();
				DrawVec3("Translation", TC.T);
				glm::vec3 rotation = glm::degrees(TC.R);
				DrawVec3("Rotation", rotation);
				TC.R = glm::radians(rotation);
				DrawVec3("Scale", TC.S, 1.0f);
				ImGui::TreePop();

				if (ent.HasComponent<LightComponent>())
				{
					ent.GetComponent<LightComponent>().Position = TC.T;
					ent.GetComponent<LightComponent>().Direction = TC.R;
				}

				if (ent.HasComponent<PointLightComponent>())
				{
					ent.GetComponent<PointLightComponent>().Position = TC.T;
				}

				if (ent.HasComponent<SpotLightComponent>())
				{
					ent.GetComponent<SpotLightComponent>().Position = TC.T;					
					ent.GetComponent<SpotLightComponent>().Direction = TC.R;
				}
			}
			ImGui::NewLine();	
		}
	
		// DIBUJADO DE CAMARA componente
		const bool hasCamera = ent.HasComponent<CameraManComponent>();
		
		if (hasCamera)
		{
			ImGui::Separator();
			ImGui::NewLine();
			if (ImGui::TreeNodeEx((void*)typeid(CameraManComponent).hash_code(), treenodeFlags, "Camera"))
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
		// DIBUJADO DE MATERIAL componente
		const bool hasLight = ent.HasComponent<LightComponent>();

		if (hasLight)
		{
			ImGui::Separator();
			ImGui::NewLine();
			if (ImGui::TreeNodeEx((void*)typeid(LightComponent).hash_code(), treenodeFlags, "Light"))
			{

				auto& ambient = ent.GetComponent<LightComponent>().Ambient;
				ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));


				auto& difusse = ent.GetComponent<LightComponent>().Difusse;
				ImGui::ColorEdit3("Difusse", glm::value_ptr(difusse));

				auto& specular = ent.GetComponent<LightComponent>().Specular;
				ImGui::ColorEdit3("Specular", glm::value_ptr(specular));


				ImGui::TreePop();

			}
			ImGui::NewLine();
		}

		// DIBUJADO DE POINTLIGHT componente
		const bool pointLight = ent.HasComponent<PointLightComponent>();

		if (pointLight)
		{
			ImGui::Separator();
			ImGui::NewLine();
			if (ImGui::TreeNodeEx((void*)typeid(PointLightComponent).hash_code(), treenodeFlags, "PointLight"))
			{

				auto& ambient = ent.GetComponent<PointLightComponent>().Ambient;
				ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));


				auto& difusse = ent.GetComponent<PointLightComponent>().Difusse;
				ImGui::ColorEdit3("Difusse", glm::value_ptr(difusse));

				auto& specular = ent.GetComponent<PointLightComponent>().Specular;
				ImGui::ColorEdit3("Specular", glm::value_ptr(specular));

				auto& linear = ent.GetComponent<PointLightComponent>().Linear;
				if (ImGui::DragFloat("Linear", &linear));
				ent.GetComponent<PointLightComponent>().Linear = linear;
			
				auto& quadratic = ent.GetComponent<PointLightComponent>().Quadratic;
				if (ImGui::DragFloat("Quadratic", &quadratic));
				ent.GetComponent<PointLightComponent>().Quadratic = quadratic;

				ImGui::TreePop();

			}
			ImGui::NewLine();
		}



		// DIBUJADO DE SPOTLIGHT componente
		const bool spotLight = ent.HasComponent<SpotLightComponent>();

		if (spotLight)
		{
			ImGui::Separator();
			ImGui::NewLine();
			if (ImGui::TreeNodeEx((void*)typeid(SpotLightComponent).hash_code(), treenodeFlags, "SpotLight"))
			{

				auto& ambient = ent.GetComponent<SpotLightComponent>().Ambient;
				ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));


				auto& difusse = ent.GetComponent<SpotLightComponent>().Difusse;
				ImGui::ColorEdit3("Difusse", glm::value_ptr(difusse));

				auto& specular = ent.GetComponent<SpotLightComponent>().Specular;
				ImGui::ColorEdit3("Specular", glm::value_ptr(specular));

				auto& linear = ent.GetComponent<SpotLightComponent>().Linear;
				if (ImGui::DragFloat("Linear", &linear));
				ent.GetComponent<SpotLightComponent>().Linear = linear;

				auto& quadratic = ent.GetComponent<SpotLightComponent>().Quadratic;
				if (ImGui::DragFloat("Quadratic", &quadratic));
				ent.GetComponent<SpotLightComponent>().Quadratic = quadratic;

				auto& outerCutOff = ent.GetComponent<SpotLightComponent>().outerCutOff;
				if (ImGui::DragFloat("outerCutOff", &outerCutOff));
				ent.GetComponent<SpotLightComponent>().outerCutOff = outerCutOff;

				ImGui::TreePop();

			}
			ImGui::NewLine();
		}


		// DIBUJADO DE MATERIAL componente
		const bool hasMaterial = ent.HasComponent<MaterialComponent>();		
	
		if (hasMaterial)
		{
			ImGui::Separator();
			ImGui::NewLine();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			bool open = ImGui::TreeNodeEx((void*)typeid(MaterialComponent).hash_code(), treenodeFlags, "Material");

			//ImGui::SameLine();
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("-", ImVec2{20, 20}))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();

			bool remove = false;

			//ImGui::NewLine();

			if (ImGui::BeginPopup("ComponentSettings"))
			{
				
				if (ImGui::MenuItem("Remove component"))
				{
					remove = true;
				}
				ImGui::EndPopup();
			}



			if (open)
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
			if (remove) ent.RemoveComponent<MaterialComponent>();
		}

		// DIBUJADO DE TEXTURA componente
		const bool hasTexture = ent.HasComponent<TextureComponent>();

		if (hasTexture)
		{
			ImGui::Separator();
			ImGui::NewLine();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			bool open = ImGui::TreeNodeEx((void*)typeid(TextureComponent).hash_code(), treenodeFlags, "Texture");

			//ImGui::SameLine();
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("-", ImVec2{ 20, 20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();

			bool remove = false;

			//ImGui::NewLine();

			if (ImGui::BeginPopup("ComponentSettings"))
			{

				if (ImGui::MenuItem("Remove component"))
				{
					remove = true;
				}
				ImGui::EndPopup();
			}



			if (open)
			{
				
				auto& Shininess = ent.GetComponent<TextureComponent>().Shininess;
				if (ImGui::DragInt("Shininess", &Shininess));
				ent.GetComponent<TextureComponent>().Shininess = Shininess;



				ImGui::TreePop();
			}
			if (remove) ent.RemoveComponent<TextureComponent>();

			ImGui::NewLine();
			ImGui::Text("Choose a texture for the selected entity:");
			ImGui::NewLine();

			if (ImGui::Button("Skulls", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/skull_low/Skulls_base.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/skull_low/Skulls_specular.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/skull_low/Skulls_normal.png";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Broken", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/low_broken/BrokenLimestoneBrickPath_basecolor.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/low_broken/BrokenLimestoneBrickPath_height.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/low_broken/BrokenLimestoneBrickPath_normal.png";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Brain", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/brain/Brain_Matter_001_COLOR.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/brain/Brain_Matter_001_SPEC.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/brain/Brain_Matter_001_NORM.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::Separator();

			if (ImGui::Button("Alien", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/alien/Metal_Alien_001_AO.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/alien/Metal_Alien_001_COLOR.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/alien/Metal_Alien_001_NRM.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("FlatRing", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/FlatRing_low/FlatRingChainmailArmor_basecolor.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/FlatRing_low/FlatRingChainmailArmor_height.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/FlatRing_low/FlatRingChainmailArmor_normal.png";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Organic", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/organic/Organic_matter_001_COLOR.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/organic/Organic_matter_001_SPEC.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/organic/Organic_matter_001_NORM.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::Separator();
			if (ImGui::Button("Gems", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/gems/Incrusted_Gems_001_COLOR.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/gems/Incrusted_Gems_001_NORM.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/gems/Incrusted_Gems_001_SPEC.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
			ImGui::SameLine();
			if (ImGui::Button("Abstract", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = "../assets/textures/abstract/Abstract_001_COLOR.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().P_S = "../assets/textures/abstract/Abstract_001_DISP.png";
				m_CollectionContext.GetComponent<TextureComponent>().P_N = "../assets/textures/abstract/Abstract_001_NRM.jpg";
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}





			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2{ 100, 20 }))
			{
				m_CollectionContext.GetComponent<TextureComponent>().P_A = m_CollectionContext.GetComponent<TextureComponent>().D_A;
				m_CollectionContext.GetComponent<TextureComponent>().P_S = m_CollectionContext.GetComponent<TextureComponent>().D_S;
				m_CollectionContext.GetComponent<TextureComponent>().P_N = m_CollectionContext.GetComponent<TextureComponent>().D_N;
				m_CollectionContext.GetComponent<TextureComponent>().SetComponentTexture();
			}
		}


		
		
		
	}

	void SceneHierarchy::DrawComponentLight(Entity ent)
	{

		const bool hasLight = ent.HasComponent<LightComponent>();
		if (hasLight)
		{

			ImGui::NewLine();
			auto& direction = ent.GetComponent<LightComponent>().Direction;
			DrawVec3("Direction", direction);
			ImGui::NewLine();
			auto& position = ent.GetComponent<LightComponent>().Position;
			DrawVec3("Position", position);			
		}
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