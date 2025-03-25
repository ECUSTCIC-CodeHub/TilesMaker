#pragma once

#include "../Layer/Layer.h"
#include "TMXLayer.h"

#include <filesystem>

namespace TileMaker
{
    class MapLayer :public Layer
    {
    public:
        MapLayer(std::filesystem::path& Path);

        MapLayer(const std::string& Name = "ImguiLayer");

        ~MapLayer();

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(const sf::Time& time) override;

        void OnEvent(const sf::Event& evnet) override;

        void OnRender() override;
    private:
        std::filesystem::path m_path;
        tmx::Map m_map;
        std::vector<std::unique_ptr<TMXLayer>> m_layers;
    };
}
