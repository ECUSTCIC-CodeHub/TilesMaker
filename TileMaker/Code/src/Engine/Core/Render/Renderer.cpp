#include "Renderer.h"

#include <SFML/Graphics/Color.hpp>

namespace TileMaker
{
    Renderer::Renderer(std::shared_ptr<sf::RenderWindow> windowForRender)
    {
        m_RenderWIndow = windowForRender;
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::BeginScence()
    {
        m_RenderWIndow->clear(sf::Color::Black);
    }

    void Renderer::EndScence()
    {
        m_RenderWIndow->display();
    }

    void Renderer::Draw()
    {

    }
}
