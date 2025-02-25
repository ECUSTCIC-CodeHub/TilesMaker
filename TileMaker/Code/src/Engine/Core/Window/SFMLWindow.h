#pragma once

#include "Window.h"
#include <SFML/Window.hpp>

namespace TileMaker
{
    class SFMLWindow : public Window
    {
    public:
        SFMLWindow();

        SFMLWindow(const SFMLWindow&) {};

        ~SFMLWindow() override;

        bool Init(const WindosSettings& windowsSettings = WindosSettings()) override;
        void ProcessEvents() override {};
        void OnUpdate() override {};
        void* GetWindowPointer() const override;
        bool isFocused() override { return false; };
        void SetEventCallback(const EventCallback& callback) override {};

        bool isOpen() override;

    private:
        sf::Window* m_window;
    };
}

