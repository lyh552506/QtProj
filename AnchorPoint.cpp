#include "AnchorPoint.hpp"

AnchorPoint::AnchorPoint(QGraphicsItem *parent)
    : QGraphicsItem(parent), m_selected(false) {
}
AnchorPoint::AnchorPoint(QPointF pos, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_selected(false) {
    this->setPos(pos);
}

QRectF AnchorPoint::boundingRect() const {
    return QRectF(-3, -3, 6, 6);
}

QPainterPath AnchorPoint::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void AnchorPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    if (isSelected()) {
        pen.setColor(Qt::blue);
        brush.setColor(Qt::cyan);
    }
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(boundingRect());
}

void AnchorPoint::setSelected(bool selected) {
    m_selected = selected;
    update();
}

void AnchorPoint::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setSelected(true);
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

void AnchorPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isSelected()) {
        setPos(mapToParent(event->pos()));
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void AnchorPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // if (event->button() == Qt::LeftButton) {
    //     setSelected(false);
    //     update();
    // }
    // QGraphicsItem::mouseReleaseEvent(event);
}