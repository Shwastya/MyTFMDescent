#include <MHelmet.h>

#define MH MHelmet  // CLIENT CALL NAMESPACE ENGINE SIDE

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using Render = MH::Renderer;
	using RenderDrawCall = MH::RenderDrawCall;
	using GeometryRender = MH::RendererGeometry;

	MyTFMDescent();	

	void Join() override;
	void Free() override;

	void Update(MH::DeltaTime dt) override;

	void ImGuiRender();

	void OnEvent(MH::Event& event) override;

private:
	MH::CameraMan m_CameraMan;

	bool m_IsActivedImGui = true;
	bool m_IsViewportOnFocus = false;
	bool m_CameraMouse = true;

	// FrameBuffer textura en el frame de ImGui
	MH::RefCount<MH::FrameBuffer> m_FrameBuffer;

	// ECS Scene
	MH::RefCount<MH::Scene> m_Scene;







	// Shader Library
	MH::ShaderLib m_S; 
	MH::RefCount<MH::Shader> Shader;

	MH::RefCount<MH::VAO> m_VAO;
	
	
	MH::RefCount<MH::Texture2D> m_Texture, m_AlphaTree;

	MH::RefCount<MH::Texture2D> m_BoardTexture;

	
	
	/* ATRIBUTOS LUZ */
	
	glm::vec3 m_LightPos{ 5.0f, 8.0f, 14.5f };

	/* ATRIBUTOS MODELO */
	ModelTransform m_Model;
	glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };		// para shader color solo


	// para IMGUI
	glm::vec2 m_ViewPortSize;

};