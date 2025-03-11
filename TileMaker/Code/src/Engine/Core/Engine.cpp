#include "Engine.h"

#include <iostream>
#include "Window/SFMLWindow.h"

#include <tmxlite/Map.hpp>
#include "TMX/TMXLayer.h"

// 测试
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


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
        map.load("./Resource/map/rpg/island.tmx"); // 因为路径问题，直接运行exe

        MapLayer layerZero(map, 0);
        MapLayer layerOne(map, 1);
        MapLayer layerThree(map, 2);
        MapLayer layerFour(map, 3);

        static_cast<sf::RenderWindow*>(window->GetWindowPointer())->setFramerateLimit(60);
        ImGui::SFML::Init(*static_cast<sf::RenderWindow*>(window->GetWindowPointer()));
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        sf::Clock deltaClock;

        while (window->isOpen())
        {
            while (const auto event = static_cast<sf::Window*>(window->GetWindowPointer())->pollEvent())
            {
                ImGui::SFML::ProcessEvent(*static_cast<sf::RenderWindow*>(window->GetWindowPointer()), *event);
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
            //layerZero.setOffset(newOffset);

            ImGui::SFML::Update(*static_cast<sf::RenderWindow*>(window->GetWindowPointer()), deltaClock.restart());
            ImGui::ShowDemoWindow();

            ImGui::Begin("Hello, world!");
            ImGui::Button("Look at this pretty button");
            ImGui::End();

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->clear(sf::Color::Black);

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->draw(layerZero);
            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->draw(layerOne);
            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->draw(layerThree);
            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->draw(layerFour);

            ImGui::SFML::Render(*static_cast<sf::RenderWindow*>(window->GetWindowPointer()));

            static_cast<sf::RenderWindow*>(window->GetWindowPointer())->display();
        }
    }
}