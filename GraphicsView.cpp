#include "GraphicsView.hpp"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
    : QGraphicsView(scene, parent), currentComponent(nullptr),
    currentWire(nullptr), currentAnchorPoint(nullptr), 
    isPlacingComponent(false), isPlacingWire(false), 
    isPlacingAnchorPoint(false), elementType(componentType::_None),
    m_zoomFactor(1.0), m_dragging(false) {
    setDragMode(QGraphicsView::NoDrag);

    setRenderHint(QPainter::Antialiasing);
    setFixedSize(850, 650);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    
    GridBackground *gridBackground = new GridBackground(scene, 10);
    scene->addItem(gridBackground);
}

template <typename T> 
void GraphicsView::putComponent(T* element, const QPointF& pos) {
    QPointF snappedPos = pos;
    snapToGrid(snappedPos, 10);
    element->setPos(snappedPos);
    scene()->addItem(element);
    for(auto anchor: element->getPoints()) {
        scene()->addItem(anchor);
    }
}

void GraphicsView::putComponent_(componentType elementType, QMouseEvent* event) {
    Component* newComponent = nullptr;
    switch (elementType) {
        case _None:
            break;
        case _Resistor:
            newComponent = new Resistor();
            break;
        case _Capacitor:
            break;
        default:
            break; 
    }
    if(newComponent)
        putComponent(newComponent, mapToScene(event->pos()));
    isPlacingComponent = false;
}

void GraphicsView::putWire(QMouseEvent *event) {
    QPointF pos = mapToScene(event->pos());
    snapToGrid(pos, 10);
    Wire *newWire = new Wire(pos);
    scene()->addItem(newWire);
    newWire->PressEvent(mapToScene(event->pos()));
    currentWire = newWire;
    // AnchorPoint* nearAnchor = findNearestAnchorPoint(pos);
    // qDebug() << "Anchor pos" << nearAnchor->pos();
    // qDebug() << "Wirestart pos" << newWire->getStartPoint();
    // if(nearAnchor && nearAnchor->pos()==newWire->getStartPoint()) 
    //     newWire->setStartAnchor(nearAnchor);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if(currentComponent!=nullptr)
        currentComponent->setSelected(false);
    if (event->button() == Qt::LeftButton) {
        if (isPlacingComponent) {
            putComponent_(elementType, event);  
        } else if (isPlacingWire) {
            putWire(event);
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
        // Drag the view
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        m_lastMousePosition = event->pos();
    } else if (isPlacingWire) { 
        if(currentWire != nullptr)
            currentWire->MoveEvent(mapToScene(event->pos()));
            // AnchorPoint* nearAnchor = findNearestAnchorPoint(pos);
            // if(nearAnchor) currentWire->setStartAnchor(nearAnchor);
    }
    else {
        QGraphicsView::mouseMoveEvent(event);
    }
}
void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::NoDrag); 
    }
    else if (isPlacingWire) {
        currentWire->ReleaseEvent(mapToScene(event->pos()));
        AnchorPoint* nearAnchor = findNearestAnchorPoint(mapToScene(event->pos()));
        if(nearAnchor && nearAnchor->pos()==currentWire->getEndPoint()) 
            currentWire->setEndAnchor(nearAnchor);
        isPlacingWire = false;
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
    QPoint pos = event->pos();
    // QPoint pos = event->position().toPoint();
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

AnchorPoint* GraphicsView::findNearestAnchorPoint(const QPointF& pos) {
    double minDistance = std::numeric_limits<double>::max();
    AnchorPoint *nearestAnchor = nullptr;
    for (QGraphicsItem *item : scene()->items()) {
        if (auto anchor = qgraphicsitem_cast<AnchorPoint *>(item)) {
            double distance = (pos - anchor->pos()).manhattanLength();
            if (distance < minDistance) {
                minDistance = distance;
                nearestAnchor = anchor;
            }
        }
    }
    return nearestAnchor;
}
