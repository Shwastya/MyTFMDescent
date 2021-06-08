#include "engine/system/node/NodeLayer.hpp"

namespace MHelmet 
{

	NodeManager::NodeManager(size_t reserve) 
	{
		// 1.
		// se calcula una reserva, tambien se puede escoger pasarlo por parametro
		m_Layers.reserve(reserve);
		//m_Layers.reserve(300);
	}
	NodeManager::~NodeManager()
	{
		
	}
	// Push en la primera MITAD de la lista
	// begin mas last index
	void NodeManager::PushLayer(NodeLayer* layer) // AddLayer
	{
		m_Layers.emplace(m_Layers.begin() + m_IdxLast, layer);
		m_IdxLast++;


		MH_CORE_WARN("Added Layer:   {0}. ", layer->GetName());

		MH_CORE_TRACE("Total Layers {0}", ++m_TotalLayers);
	}
	// Push en la segunda MITAD de la lista
	void NodeManager::PushOverlay(NodeLayer* overlay)
	{
		m_Layers.emplace_back(overlay);

		MH_CORE_WARN("Added OverLay: {0}. ", overlay->GetName());

		MH_CORE_TRACE("Total Layers {0}", ++m_TotalLayers);
	}
	void NodeManager::PopLayer(NodeLayer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_IdxLast--;
		}
	}
	
	void NodeManager::PopOverlay(NodeLayer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
			
	}
}