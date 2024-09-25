#include "GraphicsView.hpp"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
    : QGraphicsView(scene, parent), currentComponent(nullptr),
    currentWire(nullptr), isPlacingComponent(false), 
    isPlacingWire(false), elementType(componentType::_None) {
    
    setRenderHint(QPainter::Antialiasing);
    setFixedSize(800, 600);

    GridBackground *gridBackground = new GridBackground(scene, 10);
    scene->addItem(gridBackground);
}

void GraphicsView::putComponent(Component* component, const QPointF& pos) {
    QPointF snappedPos = pos;
    snapToGrid(snappedPos, 10);
    component->setPos(snappedPos);
    scene()->addItem(component);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (isPlacingComponent) {
            if(currentComponent!=nullptr)
                currentComponent->setSelected(false);
            // put conponent
            if(elementType == _Resistor) {  
                Component *newComponent = new Resistor();
                scene()->addItem(newComponent);
                putComponent(newComponent, mapToScene(event->pos()));
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
            if(currentComponent!=nullptr)
                currentComponent->setSelected(false);
            currentComponent = nullptr;
            currentWire = nullptr;
            QGraphicsView::mousePressEvent(event);

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

void GraphicsView::zoomIn() {
    m_zoomFactor *= 1.2;
    scale(1.2, 1.2);
}

void GraphicsView::zoomOut() {
    m_zoomFactor /= 1.2;
    scale(1.0 / 1.2, 1.0 / 1.2);
}

void GraphicsView::resetZoom() {
    m_zoomFactor = 1.0;
    resetTransform();
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
    QGraphicsView::wheelEvent(event);
}
