#pragma once
#include "Component.hpp"
class Resistor : public Component {
public:
    Resistor(QGraphicsItem *parent = nullptr) : Component(parent) {
        addAnchorPoint(QPointF(50, 0));
        addAnchorPoint(QPointF(50,20));
        addAnchorPoint(QPointF(0, 0));
        addAnchorPoint(QPointF(0, 20));
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final{
        Q_UNUSED(option)
        Q_UNUSED(widget)
        if (m_selected) {
            painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
            painter->drawRect(rectf);
        }else {
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::NoBrush);
            painter->drawRect(rectf);
        }
    }

};
