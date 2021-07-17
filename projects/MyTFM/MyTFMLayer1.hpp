#include <MHelmet.h>
#include "engine/system/ImGui/ImGuiDockSpace.hpp"

#include "engine/system/cameraManager/CameraFirstPerson.hpp"
#include "engine/system/cameraManager/CameraEditor.hpp"

#include "SceneHierarchy.hpp"
#include "MenuBar.hpp"
#include "BrowserPanel.hpp";


using namespace MHelmet;

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using Render = Renderer;
	using RenderDrawCall = RenderDrawCall;
	using GeometryRender = RendererGeometry;

	MyTFMDescent();
	~MyTFMDescent() = default;

	void Join() override;
	void Free() override;

	void Update(TimeStep dt) override;
	void ImGuiRender() override;
	void OnEvent(Event& event) override;

private:

	ImGuiDockSpace m_DockSpace;


	// FrameBuffer textura en el frame de ImGui
	RefCount<FrameBuffer> m_FramebufferFirstScene;
	RefCount<FrameBuffer> m_FramebufferImGuiFrame;
	RefCount<FrameBuffer> m_FramebufferPlayerCamera;
	//RefCount<FrameBuffer> m_FramebufferRedChannel;

	// ECS Scene
	RefCount<Scene> m_Scene;
	bool m_IsEditScene = true;
	bool m_EnablePostProcess = false;
	// cameramans Ents
	PerspectiveCamera m_Cam1;
	PerspectiveCamera m_Cam2;

	CameraFirstPerson m_CamMan1;
	CameraFirstPerson m_CamMan2;

	bool m_Editor_Cam_FirtsUse = true;
	//Entity Ent_CameraMan1;
	//Entity Ent_CameraMan2;
	//bool m_PrimaryCam = true;	
	//glm::vec2 m_ViewPortBounds[2];
	glm::vec2 m_viewPortSize = {0.0f, 0.0f};

	// light
	Entity Ent_Light;

	Entity Ent_PL[10]; // Points Light
	Entity Ent_SL[2];  // Spots  Light

	// panels
	SceneHierarchyUI m_HierarchyPanel;
	ContentBrowserUI m_BrowserPanel;
	MenuBarUI m_MenuBar;
	// Gizmo
	int m_GizmoType = -1;

	// BackGround Color
	glm::vec3 m_BackGroundColor = glm::vec3(0.160f, 0.286f, 0.356f);

	// info system
	std::string m_Vendor;
	std::string m_Renderer;
	std::string m_Version;
};