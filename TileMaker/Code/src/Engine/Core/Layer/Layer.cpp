#include "Layer.h"

namespace TileMaker
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

	std::string LayerStack::getLayerName(int index)
	{
        return m_Layers[index]->GetName();
	}

    std::vector<Layer*>::iterator LayerStack::begin()
    {
        return m_Layers.begin();
    }
    std::vector<Layer*>::iterator LayerStack::end()
    {
        return m_Layers.end();
    }
    std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
    {
        return m_Layers.rbegin();
    }
    std::vector<Layer*>::reverse_iterator LayerStack::rend()
    {
        return m_Layers.rend();
    }
}