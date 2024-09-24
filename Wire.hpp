#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class Wire : public QGraphicsLineItem {
public:
    Wire(QGraphicsItem *parent = nullptr) : QGraphicsLineItem(parent) {}

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        Q_UNUSED(event)
        start = mapToScene(event->pos());
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        Q_UNUSED(event)
        end = mapToScene(event->pos());
        prepareGeometryChange();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        Q_UNUSED(event)
        end = mapToScene(event->pos());
        prepareGeometryChange();
    }

    void updateGeometry() {
        setLine(start.x(), start.y(), end.x(), end.y());
    }

private:
    QPointF start, end;
};