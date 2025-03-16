#pragma once

#include "../Layer/Layer.h"
#include "imgui.h"
#include "imgui-SFML.h"

namespace TileMaker
{
    class ImguiLayer :public Layer
    {
    public:
        ImguiLayer(const std::string Name = "ImguiLayer");

        ~ImguiLayer();

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate() override;

        void OnEvent() override;
    };
}