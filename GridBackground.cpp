#include "GridBackground.hpp"
#include <QPainter>

GridBackground::GridBackground(QGraphicsScene *scene, int gridSize)
    : QGraphicsRectItem(scene->sceneRect()), gridSize(gridSize) {
    setZValue(-1000); // 确保网格在所有其他项之下
}   

void GridBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen gridPen(Qt::lightGray, 1, Qt::DotLine);
    painter->setPen(gridPen);

    QRectF rect = sceneBoundingRect();

    int left = static_cast<int>(rect.left());
    int right = static_cast<int>(rect.right());
    int top = static_cast<int>(rect.top());
    int bottom = static_cast<int>(rect.bottom());

    int firstLeft = left - (left % gridSize);
    int firstTop = top - (top % gridSize);

    for (int x = firstLeft; x <= right; x += gridSize) {
        painter->drawLine(x, top, x, bottom);
    }

    for (int y = firstTop; y <= bottom; y += gridSize) {
        painter->drawLine(left, y, right, y);
    }
}
