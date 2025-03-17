#pragma once

#include <functional>
#include <string>
#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

namespace TileMaker
{
    namespace
    {
        using EventCallback = std::function<void(void*)>;
    }

    struct WindosSettings
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindosSettings(const std::string& title = "TileMaker",
            unsigned int width = 800, unsigned int height = 600)
            : title(title), width(800), height(600)
        {
        }
    };

    class Window
    {
    public:
        Window(const WindosSettings& windowsSettings = WindosSettings());

        ~Window();

        bool Init(const WindosSettings& windowsSettings);
        
        sf::RenderWindow* GetNativeWindow() const;


        void Close();
        void SetView(const sf::View& view);

    public:
        bool isOpen = false;
        bool isFocused = false;

    private:
        std::unique_ptr<sf::RenderWindow>  m_window;

        
    };
}