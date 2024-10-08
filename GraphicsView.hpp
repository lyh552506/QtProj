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
enum statuType {
    _PlaceComponent,
    _PlaceWire,
    _PlaceAnchorPoint,
    _SetDragMode,
    _Empty,
};

class GraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    friend class Component;
    friend class AnchorPoint;
    friend class Wire;
    GraphicsView(QGraphicsScene*, QWidget* parent);
    
    template <typename T>
    void putComponent(T*, const QPointF&);
    void putComponent_(componentType, QMouseEvent*);
    void putWire(QMouseEvent*);
    void endWire(QMouseEvent*);

    void placeComponent();
    void placeWire();
    void changemode();
    void placeResistor();
    void placeCapacitor();


private:
    // component
    Component *currentComponent;
    Wire *currentWire;
    AnchorPoint *currentAnchorPoint;
    
    componentType elementType;
    statuType statu;
    // zoom
    qreal m_zoomFactor;
    // drag
    bool m_dragging;
    QPoint m_lastMousePosition;

    AnchorPoint* findAnchorPoint(const QPointF &);
    void removeCurrent();
    // template<typename T>
    // void addCurrent(T);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void wheelEvent(QWheelEvent *event);
};