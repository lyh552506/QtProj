#pragma once
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Rectangle.hpp"
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
    GraphicsView(QGraphicsScene*, QWidget* parent);
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
};