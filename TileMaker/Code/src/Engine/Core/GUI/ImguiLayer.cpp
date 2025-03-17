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
        ImGui::SFML::Init(*s_Engine->GetWindow()->GetNativeWindow());
    }

    void ImguiLayer::OnDetach()
    {
        ImGui::SFML::Shutdown();
    }

    void ImguiLayer::OnUpdate(const sf::Time& time)
    {
        ImGui::SFML::Update(*s_Engine->GetWindow()->GetNativeWindow(),time);
    }

    void ImguiLayer::OnEvent(const sf::Event& evnet)
    {
        ImGui::SFML::ProcessEvent(*s_Engine->GetWindow()->GetNativeWindow(), evnet);
    }

    void ImguiLayer::OnRender()
    {
        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        ImGui::SFML::Render(*s_Engine->GetWindow()->GetNativeWindow());
    }
}