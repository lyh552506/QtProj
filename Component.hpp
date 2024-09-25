
#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "AnchorPoint.hpp"
class Component : public QGraphicsItem {
public:
    Component(QGraphicsItem *parent);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual void paint(QPainter *painter, 
               const QStyleOptionGraphicsItem *option, 
               QWidget *widget) {}
    void setSelected(bool selected);
    inline bool isSelected() const {return m_selected;}
    QRectF rectf;
    QPointF m_lastPos;
    bool m_selected;

    void addAnchorPoint(QPointF pos);
    void removeAnchorPoint(AnchorPoint *point);
    void clearAnchorPoints();
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QList<AnchorPoint*> m_anchorPoints;
};