#include <MHelmet.h>

#define MH MHelmet  // CLIENT CALL NAMESPACE ENGINE SIDE

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using R = MH::Renderer;
	using RDC = MH::RenderDrawCall;

	MyTFMDescent();	

	void Update(MH::DeltaTime dt) override;

	void ImGuiRender();

	void OnEvent(MH::Event& event) override;

private:

	// Shader Library
	MH::ShaderLib m_S; 
	MH::RefCount<MH::Shader> Shader;

	MH::RefCount<MH::VAO>       m_VAO;
	MH::RefCount<MH::CameraMan> m_CameraMan;
	MH::RefCount<MH::Texture2D> m_Texture, m_AlphaTree;

	/* ATRIBUTOS LUZ */
	
	glm::vec3 m_LightPos{ 3.0f, 4.0f, 3.0f };
	glm::vec3 m_LightColor{ 1.0f, 1.0f, 1.0f };

	/* ATRIBUTOS MODELO */
	ModelTransform m_Model;
	glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };		// para shader color solo

};