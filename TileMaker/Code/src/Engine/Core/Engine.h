#pragma once

#include "Layer/Layer.h"
#include "Window/Window.h"
#include <memory>
#include <SFML/System/Clock.hpp>

namespace TileMaker
{

    class Engine
    {
    public:
        Engine();

        ~Engine();

        void Run();

        void OnEvent();

        Window* GetWindow();

    private:
        std::unique_ptr<Window> window;

        LayerStack layerStack;

        sf::Clock m_clock;
        sf::Clock m_globalClock;

    };

    inline Engine* s_Engine = nullptr;
}