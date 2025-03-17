#pragma once

#include <SFML/Window/Event.hpp>

namespace TileMaker
{
    class Event
    {
    public:
        Event();
        virtual ~Event() = default;
    };
}