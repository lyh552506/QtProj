#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include "AnchorPoint.hpp"
#include "GridBackground.hpp"
class Wire : public QGraphicsLineItem {
public:
    Wire(QPointF, QGraphicsItem *parent = nullptr);
    void PressEvent(QPointF);
    void MoveEvent(QPointF);
    void ReleaseEvent(QPointF);
protected:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateGeometry();

private:
    AnchorPoint *anchor_start, *anchor_end;
    QList<QPointF> pointList;
};