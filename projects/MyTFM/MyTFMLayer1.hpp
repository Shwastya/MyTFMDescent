#include <MHelmet.h>

using namespace MHelmet;

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using Render = Renderer;
	using RenderDrawCall = RenderDrawCall;
	using GeometryRender = RendererGeometry;

	MyTFMDescent();	

	void Join() override;
	void Free() override;

	void Update(DeltaTime dt) override;

	void ImGuiRender();

	void OnEvent(Event& event) override;

private:
	CameraMan m_CameraMan;

	bool m_IsActivedImGui = true;
	bool m_IsViewportOnFocus = false;
	bool m_CameraMouse = true;

	// FrameBuffer textura en el frame de ImGui
	RefCount<FrameBuffer> m_FrameBuffer;

	// ECS Scene
	RefCount<Scene> m_Scene;







	// Shader Library
	ShaderLib m_S; 
	RefCount<Shader> Shader;

	RefCount<VAO> m_VAO;
	
	
	RefCount<Texture2D> m_Texture, m_AlphaTree;

	RefCount<Texture2D> m_BoardTexture;

	
	
	/* ATRIBUTOS LUZ */
	
	glm::vec3 m_LightPos{ 5.0f, 8.0f, 14.5f };

	/* ATRIBUTOS MODELO */
	ModelTransform m_Model;
	glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };		// para shader color solo


	// para IMGUI
	glm::vec2 m_ViewPortSize;

};