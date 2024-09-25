#pragma once
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>
#include "GridBackground.hpp"
#include "Component.hpp"
#include "Wire.hpp"
#include "Resistor.hpp"

enum componentType {
    _None,
    _Resistor,
    _Capacitor,
};
class GraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    friend class Component;
    GraphicsView(QGraphicsScene*, QWidget* parent);
    void putComponent(Component*, const QPointF&);
    void placeComponent();
    void placeResistor();
    void placeCapacitor();
    void placeWire();

    void changemode();

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void wheelEvent(QWheelEvent *event);
private:
    // component
    Component *currentComponent;
    Wire *currentWire;
    bool isPlacingComponent;
    bool isPlacingWire;
    componentType elementType;
    // zoom
    qreal m_zoomFactor;
    // drag
    bool m_dragging;
    QPoint m_lastMousePosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};