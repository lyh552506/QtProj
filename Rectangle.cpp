#include "Rectangle.hpp"

RectangleItem::RectangleItem(QGraphicsItem* parent) 
    : QGraphicsItem(parent), rect(-400,-300,800,600), isDragging(false), \
    isDrawing(false), isRotating(false), rotationAngle(0.0){
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);     
}

QRectF RectangleItem::boundingRect() const {
    if(isDragging) {
        return QRectF(startPoint, endPoint).normalized();
    }
    return rect;
}

QPainterPath RectangleItem::shape() const {
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void RectangleItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                         QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawRect(boundingRect());
}

void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(!isDrawing && !isDragging) {
            isDrawing = true;
            startPoint = event->pos();
            rect = QRectF(startPoint, startPoint);
        }
        else if(isDragging){
            isDragging = true;
            lastPoint_ = event->pos();
        }
    }
}

void RectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isDrawing) {
        endPoint = event->pos();
        rect = QRectF(startPoint, endPoint).normalized();
        prepareGeometryChange();
    } else if(isDragging) {
        QPointF delta = event->pos() - lastPoint_;
        rect.translate(delta);
        lastPoint_ = event->pos();
        prepareGeometryChange();
    } 
}

void RectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos();
        rect = QRectF(startPoint, endPoint).normalized();
        isDrawing = false;
    } else if (isDragging) {
        isDragging = false;
    }
}

