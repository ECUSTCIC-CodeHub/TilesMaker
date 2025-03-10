#include "SFMLWindow.h"

#include <SFML/Graphics.hpp>

namespace TileMaker
{
    SFMLWindow::SFMLWindow()
    {
        Init();
    }


    SFMLWindow::~SFMLWindow()
    {
    }

    bool SFMLWindow::Init(const WindosSettings& windowsSettings)
    {
        WindosSettings settings;
        m_window = new sf::RenderWindow(sf::VideoMode({ settings.width,settings.height }), settings.title);
        return true;
    }

    void* SFMLWindow::GetWindowPointer() const
    {
        return m_window;
    }


    bool SFMLWindow::isOpen()
    {
        return m_window->isOpen();
    }
}