#include "GraphicsView.hpp"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
    : QGraphicsView(scene, parent), currentComponent(nullptr),
    currentWire(nullptr), isPlacingComponent(false), 
    isPlacingWire(false), elementType(componentType::_None),
    m_zoomFactor(1.0), m_dragging(false) {
    setDragMode(QGraphicsView::NoDrag);

    setRenderHint(QPainter::Antialiasing);
    setFixedSize(850, 650);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    
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
        } else if (m_dragging) {
            setDragMode(QGraphicsView::ScrollHandDrag); 
            m_lastMousePosition = event->pos();
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

    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        QPoint delta = event->pos() - m_lastMousePosition;
        // move
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        m_lastMousePosition = event->pos();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}
void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::NoDrag); 
    }
    QGraphicsView::mouseReleaseEvent(event);
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

void GraphicsView::changemode() {
    m_dragging = !m_dragging;
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

void GraphicsView::wheelEvent(QWheelEvent *event)  {
    QPoint pos = event->position().toPoint();
    QPointF scenePos = mapToScene(pos);
    QPointF center = mapFromScene(scenePos);
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        
        zoomOut();
    }
    centerOn(center);
    QGraphicsView::wheelEvent(event);
}
