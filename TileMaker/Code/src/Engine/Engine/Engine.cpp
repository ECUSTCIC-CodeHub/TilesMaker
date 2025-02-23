#include <iostream>
#include "Engine.h"
#include "ToolsTestLink.h"

namespace TileMaker
{
    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        std::cout << "Engite is runing\n";
        Tools::Test();
    }
}