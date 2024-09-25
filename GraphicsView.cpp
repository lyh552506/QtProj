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
                currentComponent = newComponent;
            }
            else if (elementType == _Capacitor) {
                
            }
            else {
                // _None
            }
            isPlacingComponent = false;
        } else if (isPlacingWire) {
            // put wire
            if (currentWire == nullptr) {
                currentWire = new Wire();
                scene()->addItem(currentWire);
                currentWire->setPos(mapToScene(event->pos()));
            }
            isPlacingWire = false;
        } else {
            // selecte a component
            QGraphicsView::mousePressEvent(event);

            // QPointF scenePos = mapToScene(event->pos());
            // QList<QGraphicsItem *> items = scene()->items(scenePos);

            // if (!items.isEmpty()) {
            //     Component *component = qgraphicsitem_cast<Component *>(items.first());
            //     if (component) {
            //         // 取消其他 Component 的选择状态
            //         for (QGraphicsItem *item : scene()->items()) {
            //             Component *comp = qgraphicsitem_cast<Component *>(item);
            //             if (comp && comp != component) {
            //                 comp->setSelected(false);
            //             }
            //         }
            //         component->setSelected(true);
            //         currentComponent = component;
            //     }
            // }
        }
    }
}
void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    // if (isPlacingWire && currentWire != nullptr) {
    //     currentWire->updateGeometry();
    // }
}
void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
    // if (isPlacingWire && currentWire != nullptr) {
    //     currentWire->updateGeometry();
    //     isPlacingWire = false;
    // } 
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

