#include "Engine.h"

#include <iostream>
#include "Window/SFMLWindow.h"


namespace TileMaker
{
    Engine::Engine()
    {
        window = new SFMLWindow();
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        while (window->isOpen())
        {
            while (const auto event = static_cast<sf::Window*>(window->GetWindowPointer())->pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    static_cast<sf::Window*>(window->GetWindowPointer())->close();
                }
            }

        }
    }
}