#include "Wire.hpp"
Wire::Wire(QPointF start, QGraphicsItem *parent) 
    : QGraphicsLineItem() {
    setZValue(1);
    setPen(QPen(Qt::black,2));
    pointList.append(start);
    // end
    pointList.append(start);
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen());
    painter->drawLine(line());
}
QRectF Wire::boundingRect() const{
    return QRectF(pointList.front(), pointList.back()).normalized();
}
void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}
void Wire::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

}
void Wire::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}
void Wire::updateGeometry() {
    setLine(pointList.front().x(), pointList.front().y(), pointList.back().x(), pointList.back().y());
}

void Wire::PressEvent(QPointF pos) {
    qDebug() << "Wire press: " << pos;
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