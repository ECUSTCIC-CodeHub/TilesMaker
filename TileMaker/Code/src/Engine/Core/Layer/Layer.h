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
        virtual void OnAttach() {};
        virtual void OnDetach() {};

        virtual void OnUpdate(const sf::Time& time) {};

        virtual void OnEvent(const sf::Event& evnet) {};

        virtual void OnRender() {};

        const std::string& GetName() const { return m_Name; };

    private:
        std::string m_Name;
    };

    // ʵ��һ��˫��ջ
    class LayerStack
    {
    public:
        LayerStack() = default;

        ~LayerStack();

        // ������
        void PushLayer(Layer* layer);
        // �Ҳ�
        void PushOverlay(Layer* overlay);

        void PopLayer(Layer* layer);

        void PopOverlay(Layer* overlay);

        std::string getLayerName(int index);

        // ��������֧��for(auto layer : layerStack)��ʽ�ı���
        std::vector<Layer*>::iterator begin();
        std::vector<Layer*>::iterator end();
        std::vector<Layer*>::reverse_iterator rbegin();
        std::vector<Layer*>::reverse_iterator rend();

    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;

    };
}