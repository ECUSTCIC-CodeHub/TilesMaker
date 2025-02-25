#pragma once

#include "Window/Window.h"

namespace TileMaker
{
    class Engine
    {
    public:
        Engine();

        ~Engine();

        void Run();

    private:
        Window* window;
    };
}