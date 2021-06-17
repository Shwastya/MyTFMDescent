#include "engine/system/node/NodeLayer.hpp"

namespace MHelmet 
{

	LayerManager::LayerManager(size_t reserve)
	{
		// 1.
		// se calcula una reserva, tambien se puede escoger pasarlo por parametro
		m_Layers.reserve(reserve);
		//m_Layers.reserve(300);
	}
	LayerManager::~LayerManager()
	{
		
	}
	// Push en la primera MITAD de la lista
	// begin mas last index
	void LayerManager::PushLayer(NodeLayer* layer) // AddLayer
	{
		m_Layers.emplace(m_Layers.begin() + m_IdxLast, layer);
		m_IdxLast++;

	}
	// Push en la segunda MITAD de la lista
	void LayerManager::PushOverlay(NodeLayer* overlay)
	{
		m_Layers.emplace_back(overlay);


	}
	void LayerManager::PopLayer(NodeLayer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_IdxLast--;
		}
	}
	
	void LayerManager::PopOverlay(NodeLayer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
			
	}
}