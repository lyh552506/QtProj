#include "GraphicsView.hpp"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
    : QGraphicsView(scene, parent), currentComponent(nullptr),
    currentWire(nullptr), currentAnchorPoint(nullptr), elementType(componentType::_None), 
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
    newComponent->setAnchorPos();
    statu = statuType::_Empty;
}

AnchorPoint* GraphicsView::findAnchorPoint(const QPointF& pos) {
    QPointF gridPos = pos;
    snapToGrid(gridPos, 10);
    QRectF rect(gridPos.x()-2, gridPos.y()-2, 4,4);
    for (QGraphicsItem *item : scene()->items(rect)) {
        if (auto component = dynamic_cast<Component*>(item)) {
            QPointF componentPos = component->pos();
            for(auto& anchor: component->getPoints()) {
                if(anchor==nullptr) continue;
                QPointF anchorPos = anchor->pos();
                anchorPos+=componentPos;
                if(anchorPos.x()==gridPos.x() && anchorPos.y()==gridPos.y()) {
                    return anchor;
                }
            }
        }
    }
    return nullptr;
}

void GraphicsView::putWire(QMouseEvent *event) {
    QPointF pos = mapToScene(event->pos());
    snapToGrid(pos, 10);
    Wire *newWire = new Wire(pos);
    scene()->addItem(newWire);
    newWire->PressEvent(mapToScene(event->pos()));
    currentWire = newWire;
    AnchorPoint* Anchor = findAnchorPoint(pos);
    if(Anchor) 
        newWire->setStartAnchor(Anchor);

}

void GraphicsView::endWire(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());
    snapToGrid(pos, 10);
    currentWire->ReleaseEvent(mapToScene(event->pos()));
    AnchorPoint* Anchor = findAnchorPoint(pos);
    if(Anchor) 
        currentWire->setEndAnchor(Anchor);
    statu = statuType::_Empty;
}

void GraphicsView::removeCurrent() {
    if(currentComponent!=nullptr)
        currentComponent->setSelected(false);
    if(currentWire!=nullptr)
        currentWire->setSelected(false);
    if(currentAnchorPoint!=nullptr) 
        currentAnchorPoint->setSelected(false);
}

void GraphicsView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete||event->key() == Qt::Key_Backspace) {
        if(currentComponent!=nullptr&&currentComponent->isSelected()) {
            scene()->removeItem(currentComponent);
            delete currentComponent;
            currentComponent = nullptr;
        }
        if(currentWire!=nullptr&&currentWire->isSelected()) {
            scene()->removeItem(currentWire);
            delete currentWire;
            currentWire = nullptr;
        }
        if(currentAnchorPoint!=nullptr&&currentAnchorPoint->isSelected()) {
            scene()->removeItem(currentAnchorPoint);
            delete currentAnchorPoint;
            currentAnchorPoint = nullptr;
        }
    }
    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    removeCurrent();
    if (event->button() == Qt::LeftButton) {
        if (statu == statuType::_PlaceComponent) {
            putComponent_(elementType, event);  
        } else if (statu == statuType::_PlaceWire) {
            putWire(event);
        } else if (m_dragging && statu == statuType::_SetDragMode) {
            setDragMode(QGraphicsView::ScrollHandDrag); 
            m_lastMousePosition = event->pos();
        } else if (statu == statuType::_Empty){
            QGraphicsView::mousePressEvent(event);
        }
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (statu == statuType::_PlaceWire) {
            if(currentWire != nullptr)
                currentWire->MoveEvent(mapToScene(event->pos()));
        } else if (m_dragging && statu == statuType::_SetDragMode) {
            // Drag the view
            QPoint delta = event->pos() - m_lastMousePosition;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            m_lastMousePosition = event->pos();
        } else {
            QGraphicsView::mouseMoveEvent(event);
        }
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (m_dragging) {
            setDragMode(QGraphicsView::NoDrag); 
        } else if (statu == statuType::_PlaceWire) {
            endWire(event);
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}
void GraphicsView::placeComponent() {
    statu = statuType::_PlaceComponent;
}
void GraphicsView::placeWire() {
    statu = statuType::_PlaceWire;
}
void GraphicsView::changemode() {
    m_dragging = !m_dragging;
    if (m_dragging)
        statu = statuType::_SetDragMode;
    else 
        statu = statuType::_Empty;
}
void GraphicsView::placeResistor() {
    elementType = componentType::_Resistor;
    placeComponent();
}
void GraphicsView::placeCapacitor() {
    elementType = componentType::_Capacitor;
    placeComponent();
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


