#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class AnchorPoint : public QGraphicsItem {
public:
    AnchorPoint(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPos(const QPointF &pos) override;
    QPointF pos() const override { return m_pos; }
    void setSelected(bool selected);
    bool isSelected() const { return m_selected; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPointF m_pos;
    bool m_selected;
};