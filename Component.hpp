
#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
class Component : public QGraphicsItem {
public:
    Component(QGraphicsItem *parent);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual void paint(QPainter *painter, 
               const QStyleOptionGraphicsItem *option, 
               QWidget *widget) = 0;
    void setSelected(bool selected);
    inline bool isSelected() const {return m_selected;}
    QRectF rectf;
    QPointF m_lastPos;
    bool m_selected;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
private:


};