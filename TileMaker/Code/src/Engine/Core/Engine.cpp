#include "Engine.h"

#include <iostream>
#include "Window/Window.h"

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
        window = std::make_unique<Window>();
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        tmx::Map map;
        map.load("./Resource/map/rpg/island.tmx"); // 因为路径问题，直接运行exe

        MapLayer layerZero(map, 0);
        MapLayer layerOne(map, 1);
        MapLayer layerThree(map, 2);
        MapLayer layerFour(map, 3);

        ImGui::SFML::Init(*static_cast<sf::RenderWindow*>(window->GetNativeWindow()));
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        sf::Clock deltaClock;

        while (window->isOpen)
        {
            sf::Time duration = m_clock.restart();

            if (window->isFocused)
            {
                OnEvent();

                for (auto& layer : layerStack)
                {
                    layer->OnUpdate(duration);
                }

                for (auto& layer : layerStack)
                {
                    layer->OnRender();
                }
            }

            //window->GetNativeWindow()->clear(sf::Color::Black);

            window->GetNativeWindow()->display();
        }
    }

    void Engine::OnEvent()
    {
        while (const auto& event = GetWindow()->GetNativeWindow()->pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                GetWindow()->Close();
                break;
            }

            if (const auto* resize = event->getIf<sf::Event::Resized>())
            {
                GetWindow()->SetView(sf::View(sf::FloatRect({ 0, 0 }, { resize->size.x , resize->size.y })));
            }
            else
            {
                for (auto& layer : layerStack)
                {
                    layer->OnEvent(event.value());
                }
            }
        }


        GetWindow()->GetNativeWindow()->handleEvents(
            [&](const sf::Event::Closed&)
            {
                GetWindow()->Close();
            },
            [&](const sf::Event::Resized& event)
            {
                GetWindow()->SetView(sf::View(sf::FloatRect({ 0, 0 }, { event.size.x, event.size.y })));
            },
            [&](const auto& event)
            {
                std::optional<sf::Event> optEvent = event;

                for (auto& layer : layerStack)
                {
                    layer->OnEvent(optEvent);
                }
            });
    }
    Window* Engine::GetWindow()
    {
        return window.get();
    }
}