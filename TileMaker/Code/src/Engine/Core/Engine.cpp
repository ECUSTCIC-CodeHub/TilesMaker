#include "Engine.h"

#include <iostream>
#include "Window/SFMLWindow.h"

#include <tmxlite/Map.hpp>
#include "TMX/TMXLayer.h"

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
        tmx::Map map;
        sf::Clock globalClock;
        sf::Clock wiggleClock;
        map.load("./Resource/map/demo.tmx"); // 因为路径问题，直接运行exe

        MapLayer layerZero(map, 0);

        while (window->isOpen())
        {
            while (const auto event = static_cast<sf::Window*>(window->GetWindowPointer())->pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    static_cast<sf::Window*>(window->GetWindowPointer())->close();
                }
            }
            sf::Time duration = globalClock.restart();
            layerZero.update(duration);

            sf::Vector2f newOffset = sf::Vector2f(0.f, 0.f);
            if (true)
            {
                newOffset = sf::Vector2f(std::cos(wiggleClock.getElapsedTime().asSeconds()) * 100.f, 0.f);
            }
            layerZero.setOffset(newOffset);

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->clear(sf::Color::Black);

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->draw(layerZero);

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->display();
        }
    }
}