#pragma once

#include <vector>
#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace TileMaker
{
    class Layer
    {
    public:
        Layer(const std::string Name = "BaseLayer")
            :m_Name(Name)
        {}

        // 析构定义为虚函数，避免内存泄漏
        virtual ~Layer();

        // 提供扩展性的东西，项目除基础组件之外都要继承他
        virtual void OnAttach();
        virtual void OnDetach();

        virtual void OnUpdate(const sf::Time& time);

        virtual void OnEvent(const sf::Event& evnet);

        virtual void OnRender();

        const std::string& GetName() const;

    private:
        std::string m_Name;
    };

    // 实现一个双端栈
    class LayerStack
    {
    public:
        LayerStack();

        ~LayerStack();

        // 左侧插入
        void PushLayer(Layer* layer);
        // 右侧
        void PushOverlay(Layer* overlay);

        void PopLayer(Layer* layer);

        void PopOverlay(Layer* overlay);

        // 迭代器，支持for(auto layer : layerStack)形式的遍历
        std::vector<Layer*>::iterator begin();
        std::vector<Layer*>::iterator end();

    private:
        std::vector<Layer*> m_Layers;

    };
}