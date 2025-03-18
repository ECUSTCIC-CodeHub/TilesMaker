#include "Window.h"


namespace TileMaker
{
    Window::Window(const WindosSettings& windowsSettings)
    {
        Init(windowsSettings);

    }

    Window::~Window()
    {
    }

    bool Window::Init(const WindosSettings& windowsSettings)
    {
        m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode({ windowsSettings.width,windowsSettings.height }), 
            windowsSettings.title);

        m_window->setFramerateLimit(60);

        return true;
    }

    sf::RenderWindow* Window::GetNativeWindow() const
    {
        return m_window.get();
    }

    void Window::Close()
    {
        m_window->close();
    }

    void Window::SetView(const sf::View& view)
    {
        m_window->setView(view);
    }
}