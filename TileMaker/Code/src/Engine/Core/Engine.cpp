#include <iostream>
#include <SFML/Window.hpp>
#include "Engine.h"


namespace TileMaker
{
    Engine::Engine()
    {
        sf::Window window(sf::VideoMode({ 800, 600 }), "TileMaker");
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        // init

    }
}