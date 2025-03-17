#pragma once

#include "Layer/Layer.h"
#include "SFML/System/Clock.hpp"
#include "Window/Window.h"
#include <memory>

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

    static Engine* s_Engine = new Engine(); // 全局变量实现单例模式
}