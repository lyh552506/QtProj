#include "AnchorPoint.hpp"
#include "GraphicsView.hpp"
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
        pen.setColor(Qt::red);
    } else {
        pen.setColor(Qt::black);
        // brush.setColor(Qt::white);
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
        for (auto view : scene()->views()) {
            if (GraphicsView* gview = qobject_cast<GraphicsView*>(view)) {
                gview->currentAnchorPoint = this;
                setSelected(true);
                break;
            }
        }
    }
}

void AnchorPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

}

void AnchorPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}