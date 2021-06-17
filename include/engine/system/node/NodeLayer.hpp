#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/node/Node.hpp"

namespace MHelmet
{	
	struct NodeLayer : public Node
	{
		NodeLayer() {};
//#if MH_DEBUG
		NodeLayer(const std::string& name = "noname") : m_Name(name) {};
//#endif
		virtual ~NodeLayer() {};

		// Node base
		virtual void Join() override { CORE_TRACE("Joined Layer: {0}", m_Name); };	
		virtual void Free() override { CORE_TRACE("Freed  Layer: {0}", m_Name); };

		virtual void Update(DeltaTime dt) override {};	// Node base

		virtual void ImGuiRender() {};		// propio

		virtual void OnEvent(Event& e) {}	// propio

//#if MH_DEBUG
		inline const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
//#endif
	};

	class LayerManager
	{
	public:
	
		//using PrtLayer   = std::shared_ptr<NodeLayer>;
		//using LayerGrp = std::vector<std::shared_ptr<NodeLayer>>;

		LayerManager(size_t reserve = 10);
		~LayerManager();

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