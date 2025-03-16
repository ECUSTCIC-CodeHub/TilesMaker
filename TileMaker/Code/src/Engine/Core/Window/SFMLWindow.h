#pragma once

#include "Window.h"
#include <SFML/Graphics.hpp>

namespace TileMaker
{
    class SFMLWindow : public Window
    {
    public:
        SFMLWindow();

        SFMLWindow(const SFMLWindow&) {};

        ~SFMLWindow() override;

        bool Init(const WindosSettings& windowsSettings = WindosSettings()) override;
        void* GetNativeWindow() const override;
        bool isFocused() override { return false; };
        void SetEventCallback(const EventCallback& callback) override {};

        bool isOpen() override { return true; };

    private:
        sf::RenderWindow * m_window;
    };
}

