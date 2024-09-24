#include "Component.hpp"

Component::Component(QGraphicsItem *parent = nullptr) : 
    QGraphicsItem(parent),  m_selected(false){}
QRectF Component::boundingRect() const{
    return QRectF(0, 0, 50, 50);
} 

QPainterPath Component::shape() const {
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void Component::setSelected(bool selected)
{
    m_selected = selected;
    update();
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setSelected(true);
        m_lastPos = event->pos();
    }
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_selected) {
        QPointF newPos = event->scenePos();
        QPointF delta = newPos - m_lastPos;
        setPos(pos() + delta);
        m_lastPos = newPos;
    }
    update();
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setSelected(false);
        update();
    }
}