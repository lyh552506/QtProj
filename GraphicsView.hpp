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
#include "AnchorPoint.hpp"
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
    
    template <typename T>
    void putComponent(T*, const QPointF&);
    void putComponent_(componentType, QMouseEvent*);
    void putWire(QMouseEvent*);

    void placeComponent();
    void placeResistor();
    void placeCapacitor();
    void placeWire();
    void changemode();


private:
    // component
    Component *currentComponent;
    Wire *currentWire;
    AnchorPoint *currentAnchorPoint;
    bool isPlacingComponent;
    bool isPlacingWire;
    bool isPlacingAnchorPoint;
    componentType elementType;
    // zoom
    qreal m_zoomFactor;
    // drag
    bool m_dragging;
    QPoint m_lastMousePosition;

    AnchorPoint* findNearestAnchorPoint(const QPointF &);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void wheelEvent(QWheelEvent *event);
};