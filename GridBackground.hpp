#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class GridBackground : public QGraphicsRectItem {
public:
    GridBackground(QGraphicsScene *scene, int gridSize = 20);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
private:
    int gridSize;
};