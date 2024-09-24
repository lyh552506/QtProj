#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Rectangle.hpp"
#include "Component.hpp"
#include "Wire.hpp"
#include "Resistor.hpp"
class GraphicsView : public QGraphicsView {
public:
    GraphicsView(QGraphicsScene*, QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void placeComponent();
    void placeWire() ;
private:
    Component *currentComponent;
    Wire *currentWire;
    bool isPlacingComponent;
    bool isPlacingWire;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitToolBar();
    void showToolBar(QToolBar*);

    void InitGraph();

private:
    // QMenuBar* menuBar;
    QMenu* menuToolBar;
    QMenu* menuTest_put;
    QMenu* menuTest_file;

    QToolBar* toolBar;
    QToolBar* toolBar_put;
    QToolBar* toolBar_file;

    QAction* actionTest;
    QAction* actionTest_put;
    QAction* actionTest_file;
    QAction* put;
    QAction* file;

    QGraphicsScene* scene;
    QGraphicsView* view;
private slots:
    void on_put_triggered();
    void on_file_triggered();
};
#endif // MAINWINDOW_H
