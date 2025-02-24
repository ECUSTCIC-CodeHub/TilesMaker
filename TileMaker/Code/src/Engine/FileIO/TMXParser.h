#pragma once

#include "TMX/TMXMap.h"

namespace TileMaker
{
    class TMXParser
    {
    public:
        TMXParser();

        ~TMXParser();

        static Tools::TMXMap* Parse(const std::string& tmxFile);
    };
}
