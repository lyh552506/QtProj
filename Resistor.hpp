#pragma once
#include "Component.hpp"
class Resistor : public Component {
public:
    Resistor(QGraphicsItem *parent = nullptr) : Component(parent) {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final{
        Q_UNUSED(option)
        Q_UNUSED(widget)
        
        painter->setPen(QPen(Qt::black, 2));
        painter->setBrush(Qt::NoBrush);
        rect = boundingRect();
        painter->drawRect(rect);

        if (m_selected) {
            painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
            painter->drawRect(rect);
        }
    }

};
