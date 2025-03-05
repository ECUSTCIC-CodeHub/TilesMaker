#pragma once

#include <tmxlite/Map.hpp>
#include <vector>


namespace TileMaker
{
    using MapLayer = std::vector<tmx::Layer::Ptr>;
    class TMXData
    {
    public:
        TMXData(const tmx::Map& map);

        ~TMXData();


    private:
        std::vector<MapLayer> m_layers;
    };
    
}
