#include "Component.hpp"
#include "GraphicsView.hpp"
Component::Component(QGraphicsItem *parent) : 
    QGraphicsItem(parent),  m_selected(false){
        rectf = boundingRect();
}
QRectF Component::boundingRect() const{
    return QRectF(0, 0, 50, 25);
} 

QPainterPath Component::shape() const {
    QPainterPath path;
    path.addRect(rectf);
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
        m_lastPos = event->scenePos();
        for (auto view : scene()->views()) {
            if (GraphicsView* gview = qobject_cast<GraphicsView*>(view)) {
                gview->currentComponent = this;
            }
        }
    }

}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_selected) {
        QPointF newPos = event->scenePos();
        QPointF delta = newPos - m_lastPos;
        setPos(pos() + delta);
        m_lastPos = newPos;
        update();
    }
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // if (event->button() == Qt::LeftButton) {
    //     setSelected(false);
    //     update();
    // }
}