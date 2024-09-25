#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <cmath>
void snapToGrid(QPointF&, int);
class GridBackground : public QGraphicsRectItem {
public:
    GridBackground(QGraphicsScene *scene, int gridSize = 20);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
private:
    int gridSize;
};