#include "MapLayer.h"

#include "../Engine/Core/Engine.h"

namespace TileMaker
{

    MapLayer::MapLayer(std::filesystem::path& Path)
        :Layer(Path.filename().string())
    {
        if (!std::filesystem::exists(Path))
        {
            std::cout << "tmx file is not exists in " << Path.string() << std::endl;
            return;
        }
        m_path = Path;
    }

    MapLayer::~MapLayer()
    {
    }

    void MapLayer::OnAttach()
    {
        m_map.load(m_path.string());

        for (int i = 0; i < m_map.getLayers().size(); i++)
        {
            m_layers.emplace_back(std::make_unique<TMXLayer>(m_map, i));
        }
    }

    void MapLayer::OnDetach()
    {
    }

    void MapLayer::OnUpdate(const sf::Time& time)
    {
        for (auto& layer : m_layers)
        {
            layer->update(time);
        }
    }

    void MapLayer::OnEvent(const sf::Event& evnet)
    {
        
    }

    void MapLayer::OnRender()
    {
        for (auto& layer : m_layers)
        {
            s_Engine->GetWindow()->GetNativeWindow()->draw(*layer);
        }
    }
}