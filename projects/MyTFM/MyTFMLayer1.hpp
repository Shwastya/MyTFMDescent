#include <MHelmet.h>
#include "SceneHierarchy.hpp"

using namespace MHelmet;

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using Render = Renderer;
	using RenderDrawCall = RenderDrawCall;
	using GeometryRender = RendererGeometry;

	MyTFMDescent();	
	~MyTFMDescent() {  }

	void Join() override;
	void Free() override;

	void Update(DeltaTime dt) override;

	void ImGuiRender();

	void OnEvent(Event& event) override;

private:
	
	//bool m_IsViewportOnFocus = false;	

	// FrameBuffer textura en el frame de ImGui
	RefCount<FrameBuffer> m_FrameBuffer;
	 
	// ECS Scene
	RefCount<Scene> m_Scene;
	bool m_IsEditScene = true;

	// cameramans Ents
	Entity Ent_CameraMan1; bool m_Editor_Cam_FirtsUse = true;
	Entity Ent_CameraMan2;
	bool m_PrimaryCam = true;	

	// light
	Entity Ent_Light;

	Entity E_PL[10];

	Entity Ent_SpotLight1;
	Entity Ent_SpotLight2;

	// panels
	SceneHierarchy m_HierarchyPanel;

	// Gizmo
	int m_GizmoType = -1;


	// de prueba
	Entity Ent_probandoTexturas;



	// Shader Library
	//ShaderLib m_S; 
	//RefCount<Shader> Shader;

	//RefCount<VAO> m_VAO;
	
	
	//RefCount<Texture2D> m_Texture, m_AlphaTree;

	//RefCount<Texture2D> m_BoardTexture;

	
	
	/* ATRIBUTOS LUZ */
	
	//glm::vec3 m_LightPos{ 0.0f, 8.0f, 14.5f };

	/* ATRIBUTOS MODELO */
	//ModelTransform m_Model;
	//glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };		// para shader color solo


	// para IMGUI
	//glm::vec2 m_ViewPortSize;

};