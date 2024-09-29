#include "Wire.hpp"
#include "GraphicsView.hpp"
Wire::Wire(QPointF start, QGraphicsItem *parent) 
    : QObject(), QGraphicsLineItem(),
    anchor_start(nullptr), anchor_end(nullptr) {
    setZValue(1);
    setPen(QPen(Qt::black,2));
    pointList.append(start);
    // end point
    pointList.append(start);
    setLine(start.x(), start.y(), start.x(), start.y());
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(m_selected) {
        painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
    }
    else {
        painter->setPen(QPen(Qt::black, 2));
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawLine(line());

}
QRectF Wire::boundingRect() const{
    return QRectF(pointList.front(), pointList.back()).normalized();
}

void Wire::setSelected(bool selected) {
    m_selected = selected;
    update();
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        for (auto view : scene()->views()) {
            if (GraphicsView* gview = qobject_cast<GraphicsView*>(view)) {
                gview->currentWire = this;
                setSelected(true);
                break;
            }
        }
    }
}

void Wire::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

}
void Wire::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}
void Wire::updateGeometry() {
    if(anchor_start) {
        QPointF startPos = anchor_start->getAnchorPos();
        pointList.front() = startPos;
    }
    if(anchor_end) {
        QPointF EndPos = anchor_end->getAnchorPos();
        pointList.back() = EndPos;
    }
    setLine(pointList.front().x(), pointList.front().y(), pointList.back().x(), pointList.back().y());
}

void Wire::PressEvent(QPointF pos) {
    snapToGrid(pos, 10);
    pointList.front() = pos;
    updateGeometry();
    prepareGeometryChange();
}
void Wire::MoveEvent(QPointF pos) {
    snapToGrid(pos, 10);
    pointList.back() = pos;
    updateGeometry();
    prepareGeometryChange();
}
void Wire::ReleaseEvent(QPointF pos) {
    snapToGrid(pos, 10);
    pointList.back() = pos;
    updateGeometry();
    prepareGeometryChange();
}

void Wire::setStartAnchor(AnchorPoint* start) {
    anchor_start = start;
    if(anchor_start) {
        connect(anchor_start, &AnchorPoint::positionChanged, 
                this, &Wire::updateGeometry);
    }
    updateGeometry();
}
void Wire::setEndAnchor(AnchorPoint* end) {
    if(anchor_start) {
        connect(anchor_start, &AnchorPoint::positionChanged, 
                this, &Wire::updateGeometry);
    }
    updateGeometry();
}