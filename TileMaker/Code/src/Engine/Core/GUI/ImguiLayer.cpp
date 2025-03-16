#include "ImguiLayer.h"
#include "../Engine.h"

namespace TileMaker
{
    ImguiLayer::ImguiLayer(const std::string Name)
        :Layer(Name)
    {
    }

    ImguiLayer::~ImguiLayer()
    {
    }

    void ImguiLayer::OnAttach()
    {
        ImGui::SFML::Init(*static_cast<sf::RenderWindow*>(s_Engine->GetWindow()->GetNativeWindow()));
    }

    void ImguiLayer::OnDetach()
    {
        ImGui::SFML::Shutdown();
    }

    void ImguiLayer::OnUpdate()
    {
        ImGui::SFML::Update(*static_cast<sf::RenderWindow*>(s_Engine->GetWindow()->GetNativeWindow()), deltaClock.restart());
    }

    void ImguiLayer::OnEvent()
    {

    }
}