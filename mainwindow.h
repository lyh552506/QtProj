#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qaction.h>
#include <qchar.h>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>
#include <QToolBar>
#include "Component.hpp"
#include "Rectangle.hpp"
#include "Resistor.hpp"
#include "Wire.hpp"

class GraphicsView : public QGraphicsView {
 public:
  GraphicsView(QGraphicsScene*, QWidget* parent);
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void placeComponent();
  void placeWire();

 private:
  Component* currentComponent;
  Wire* currentWire;
  bool isPlacingComponent;
  bool isPlacingWire;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
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
  QAction* action_Open;
  QAction* action_Save;
  QAction* put;
  QAction* file;

  QGraphicsScene* scene;
  QGraphicsView* view;

  QString current_file;
 private slots:
  void on_put_triggered();
  void on_file_triggered();
  void open_file_triggered();
  void save_file_triggered();
};
#endif  // MAINWINDOW_H
