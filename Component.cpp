#include "Component.hpp"
#include "GraphicsView.hpp"
Component::Component(QGraphicsItem *parent) : 
    QGraphicsItem(parent),  m_selected(false){
        rectf = boundingRect();
}
QRectF Component::boundingRect() const{
    QRectF rect(0, 0, 50, 20);
    for (AnchorPoint *point : m_anchorPoints) {
        rect = rect.united(point->boundingRect());
    }
    return rect;
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

void Component::addAnchorPoint(QPointF pos) {
    AnchorPoint *point = new AnchorPoint(pos, this, this);
    m_anchorPoints.append(point);
}

void Component::removeAnchorPoint(AnchorPoint *point) {
    m_anchorPoints.removeOne(point);
    delete point;
}

void Component::clearAnchorPoints() {
    while (!m_anchorPoints.isEmpty()) {
        removeAnchorPoint(m_anchorPoints.first());
    }
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastPos = event->scenePos();
        for (auto view : scene()->views()) {
            if (GraphicsView* gview = qobject_cast<GraphicsView*>(view)) {
                gview->currentComponent = this;
                setSelected(true);
                break;
            }
        }
    }

}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_selected) {
        QPointF newPos = event->scenePos();
        move(newPos);
    }
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QPointF newPos = event->scenePos();
    move(newPos);
}

void Component::move(QPointF newPos) {
    QPointF delta = newPos - m_lastPos;
    if(abs(delta.x())>=10 || abs(delta.y())>=10 ) {
        snapToGrid(delta, 10);
        setPos(pos() + delta);
        m_lastPos = newPos;
        for (AnchorPoint *point : m_anchorPoints) {
            point->positionChanged(pos() + delta);
        }
        update();
    }
    for(AnchorPoint* point: m_anchorPoints) {
        QPointF local = mapToScene(point->pos());
        point->setAnchorPos(local);
        point->positionChanged(local);
        qDebug() << point->getAnchorPos();
    }

}
void Component::setAnchorPos() {
    for(auto& point: m_anchorPoints) {
        point->setAnchorPos(pos()+point->pos());
        qDebug() << point->getAnchorPos();
    }
}