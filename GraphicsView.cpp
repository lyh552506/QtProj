#include "GraphicsView.hpp"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
    : QGraphicsView(scene, parent), currentComponent(nullptr),
    currentWire(nullptr), isPlacingComponent(false), 
    isPlacingWire(false), elementType(componentType::_None) {}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (isPlacingComponent) {
            // put conponent
            if(elementType == _Resistor) {  
                Component *newComponent = new Resistor();
                scene()->addItem(newComponent);
                newComponent->setPos(mapToScene(event->pos()));
                isPlacingComponent = false;
            }
            else if (elementType == _Capacitor) {
                
            }
            else {
                // _None
            }
        } else if (isPlacingWire) {
            // put wire
            if (currentWire == nullptr) {
                currentWire = new Wire();
                scene()->addItem(currentWire);
                currentWire->setPos(mapToScene(event->pos()));
            }
        } else {
            // selecte a component
            QPointF pos = event->pos(); 
            QList<QGraphicsItem *> items = scene()->items(pos);
            if (!items.isEmpty()) {
                Component *component = qgraphicsitem_cast<Component *>(items.first());
                if (component) {
                    component->setSelected(true);
                }
            }
        }
    }
}
void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (isPlacingWire && currentWire != nullptr) {
        currentWire->updateGeometry();
    }
}
void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (isPlacingWire && currentWire != nullptr) {
        currentWire->updateGeometry();
        isPlacingWire = false;
    }
}
void GraphicsView::placeComponent() {
    isPlacingComponent = true;
}
void GraphicsView::placeResistor() {
    elementType = componentType::_Resistor;
    placeComponent();
}
void GraphicsView::placeCapacitor() {
    elementType = componentType::_Capacitor;
    placeComponent();
}

void GraphicsView::placeWire() {
    isPlacingWire = true;
}