#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class AnchorPoint : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    AnchorPoint(QGraphicsItem *parent = nullptr);
    AnchorPoint(QPointF pos, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setSelected(bool selected);
    bool isSelected() const { return m_selected; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void positionChanged(const QPointF& pos);

private:
    bool m_selected;
};