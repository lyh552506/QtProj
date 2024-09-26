#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class AnchorPoint : public QGraphicsItem {
public:
    AnchorPoint(QGraphicsItem *parent = nullptr);
    AnchorPoint(QPointF pos, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setSelected(bool selected);
    bool isSelected() const { return m_selected; }
    inline QPointF getPos() const {return m_pos;}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPointF m_pos;
    bool m_selected;
};