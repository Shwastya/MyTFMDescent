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

	Entity Ent_PL[10]; // Points Light
	Entity Ent_SL[2];  // Spots  Light

	// panels
	SceneHierarchy m_HierarchyPanel;

	// Gizmo
	int m_GizmoType = -1;

	// BackGround Color
	glm::vec3 m_BackGroundColor = glm::vec3(0.171f, 0.328f, 0.485f);

	// de prueba
	Entity Ent_probandoTexturas;

	// info system
	std::string m_Vendor;
	std::string m_Renderer;
	std::string m_Version;

};