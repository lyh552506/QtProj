#include <QGraphicsItem>
#include <QPainter>

class Component : public QGraphicsItem {
public:
    Component(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent) {}

    QRectF boundingRect() const override {
        return QRectF(-10, -10, 20, 20);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->drawEllipse(boundingRect());
    }
};