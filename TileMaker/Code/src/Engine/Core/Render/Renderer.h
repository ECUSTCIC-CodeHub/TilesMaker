#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace TileMaker
{
    class Renderer
    {
    public:

        Renderer() = delete;
        Renderer(std::shared_ptr<sf::RenderWindow> windowForRender);

        ~Renderer();

        void BeginScence();

        void EndScence();

        void Draw();
    private:
        std::shared_ptr<sf::RenderWindow> m_RenderWIndow;
    };

}

