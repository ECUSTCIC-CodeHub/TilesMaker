#pragma once

#include "Window/Window.h"
#include "Layer/Layer.h"
#include <memory>

namespace TileMaker
{
    class Engine
    {
    public:
        Engine();

        ~Engine();

        void Run();

        Window* GetWindow();

    private:
        std::unique_ptr<Window> window;

        LayerStack layerStack;
    };

    static Engine* s_Engine = new Engine(); // 全局变量实现单例模式
}