#include "AnchorPoint.hpp"

AnchorPoint::AnchorPoint(QGraphicsItem* m_parent, QGraphicsItem *parent)
    : QObject(), QGraphicsItem(parent), m_selected(false),
    m_parent(m_parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}
AnchorPoint::AnchorPoint(QPointF pos_, QGraphicsItem* m_parent, QGraphicsItem *parent)
    : QObject(), QGraphicsItem(parent), m_selected(false),
    m_parent(m_parent) {
    this->setPos(pos_);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
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
}

void AnchorPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

}

void AnchorPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}