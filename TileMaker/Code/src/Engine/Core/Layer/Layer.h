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

        // ��������Ϊ�麯���������ڴ�й©
        virtual ~Layer();

        // �ṩ��չ�ԵĶ�������Ŀ���������֮�ⶼҪ�̳���
        virtual void OnAttach();
        virtual void OnDetach();

        virtual void OnUpdate(const sf::Time& time);

        virtual void OnEvent(const sf::Event& evnet);

        virtual void OnRender();

        const std::string& GetName() const;

    private:
        std::string m_Name;
    };

    // ʵ��һ��˫��ջ
    class LayerStack
    {
    public:
        LayerStack();

        ~LayerStack();

        // ������
        void PushLayer(Layer* layer);
        // �Ҳ�
        void PushOverlay(Layer* overlay);

        void PopLayer(Layer* layer);

        void PopOverlay(Layer* overlay);

        // ��������֧��for(auto layer : layerStack)��ʽ�ı���
        std::vector<Layer*>::iterator begin();
        std::vector<Layer*>::iterator end();

    private:
        std::vector<Layer*> m_Layers;

    };
}