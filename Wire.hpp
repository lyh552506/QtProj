#pragma once
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QObject>
#include "AnchorPoint.hpp"
#include "GridBackground.hpp"
class Wire : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    Wire(QPointF, QGraphicsItem *parent = nullptr);
    void setStartAnchor(AnchorPoint*);
    void setEndAnchor(AnchorPoint*);
    void PressEvent(QPointF);
    void MoveEvent(QPointF);
    void ReleaseEvent(QPointF);
    inline QPointF& getStartPoint() {return pointList.front();}
    inline QPointF& getEndPoint() {return pointList.back();}

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