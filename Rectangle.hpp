#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
class RectangleItem: public QGraphicsItem {
public:
    RectangleItem(QGraphicsItem* parent=nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QRectF rect;
    QPointF startPoint;
    QPointF endPoint;
    bool isDragging;
    bool isRotating;
    bool isDrawing;
    qreal rotationAngle;
    QPointF lastPoint_;
    QPointF rotationCenter;
    qreal lastAngle;
};