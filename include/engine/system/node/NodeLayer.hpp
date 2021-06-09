#pragma once
#include "engine/system/node/Node.hpp"
#include "engine/system/MHCore.hpp"

namespace MHelmet
{	
	struct NodeLayer : public Node
	{
		NodeLayer() {};
//#if MH_DEBUG
		NodeLayer(const std::string& name = "noname") : m_Name(name) {};
//#endif
		virtual ~NodeLayer() {};

		virtual void Join() override {};	// Node base
		virtual void Free() override {};	// Node base

		virtual void Update() override {};	// Node base

		virtual void ImGuiRender() {};

		virtual void OnEvent(Event& e) {}

//#if MH_DEBUG
		inline const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
//#endif
	};

	class NodeManager
	{
	public:
	
		//using PrtLayer   = std::shared_ptr<NodeLayer>;
		//using LayerGrp = std::vector<std::shared_ptr<NodeLayer>>;

		NodeManager(size_t reserve = 300);
		~NodeManager();

		void PushLayer(NodeLayer* layer); //AddLayer		
		void PushOverlay(NodeLayer* overlay);

		void PopLayer(NodeLayer* layer);
		void PopOverlay(NodeLayer* overlay);

		//LayerGrp::iterator begin() { return m_Layers.begin(); }
		//LayerGrp::iterator end() { return m_Layers.end(); }

		std::vector<NodeLayer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<NodeLayer*>::iterator end()   { return m_Layers.end(); }
	
		
	private:
		 
		//LayerGrp m_Layers;
		std::vector<NodeLayer*> m_Layers;

		uint32_t m_IdxLast = 0;

		uint32_t m_TotalLayers = 0;
	};

}