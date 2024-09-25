#pragma once
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
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
    void snapToGrid(QPointF&, int);
    void putComponent(Component*, const QPointF&);
    void placeComponent();
    void placeResistor();
    void placeCapacitor();
    void placeWire();
private:
    Component *currentComponent;
    Wire *currentWire;
    bool isPlacingComponent;
    bool isPlacingWire;
    componentType elementType;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    // void selectComponent(Component*);
};