#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QDebug>
#include <QGraphicsView>

class AnchorPoint : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    AnchorPoint(QGraphicsItem*, QGraphicsItem *parent = nullptr);
    AnchorPoint(QPointF pos, QGraphicsItem*, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setSelected(bool selected);
    bool isSelected() const { return m_selected; }
    inline QGraphicsItem*& getParent() {return m_parent;}
    inline void setAnchorPos(QPointF pos) {m_pos = pos;}
    inline QPointF getAnchorPos() const {return m_pos;}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void positionChanged(const QPointF& pos);

private:
    QGraphicsItem* m_parent;
    bool m_selected;
    QPointF m_pos;
};