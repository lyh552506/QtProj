#pragma once
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
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

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void wheelEvent(QWheelEvent *event);
private:
    Component *currentComponent;
    Wire *currentWire;
    bool isPlacingComponent;
    bool isPlacingWire;
    componentType elementType;
    qreal m_zoomFactor;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};