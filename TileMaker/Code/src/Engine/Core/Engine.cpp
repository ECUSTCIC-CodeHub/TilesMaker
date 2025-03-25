#include "Engine.h"
#include "GUI/ImguiLayer.h"
#include "TMX/MapLayer.h"
#include "TMX/TMXLayer.h"
#include "Window/Window.h"

#include <iostream>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


namespace TileMaker
{
    Engine::Engine()
    {
        s_Engine = this;
        window = std::make_unique<Window>();
        layerStack.PushLayer(new ImguiLayer());
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        std::filesystem::path p = "C:/Code/ECUSTCIC-CodeHub/TilesMaker/TileMaker/bin/Release-windows-x86_64/TilesMakerApp/Resource/map/rpg/island.tmx";
        MapLayer map(p);

        layerStack.PushLayer(&map);

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

                window->GetNativeWindow()->clear(sf::Color::Black);

                for (auto& layer : layerStack)
                {
                    layer->OnRender();
                }
            }


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
                GetWindow()->SetView(sf::View(sf::FloatRect({ 0.f, 0.f }, { (float)resize->size.x , (float)resize->size.y })));
            }
            else
            {
                for (auto& layer : layerStack)
                {
                    layer->OnEvent(event.value());
                }
            }
        }
    }

    Window* Engine::GetWindow()
    {
        return window.get();
    }
}