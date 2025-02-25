#pragma once

#include <functional>
#include <string>

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
        Window() {};

        virtual ~Window() = default;

        virtual bool Init(const WindosSettings& windowsSettings = WindosSettings()) = 0;
        virtual void ProcessEvents() = 0;
        virtual void OnUpdate() {};
        
        virtual void* GetWindowPointer() const = 0;
        
        virtual bool isOpen() = 0;
        virtual bool isFocused() = 0;

        virtual void SetEventCallback(const EventCallback& callback) = 0;

    };
}