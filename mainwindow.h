#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <qaction.h>
#include <qevent.h>
#include <qchar.h>
#include "GraphicsView.hpp"


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
  QAction* action_Resistor;
  QAction* action_DragMode;

  QGraphicsScene* scene;
  GraphicsView* view;

  QString current_file;

private slots:
  void on_put_triggered();
  void on_file_triggered();
  void open_file_triggered();
  void save_file_triggered();
  
  void on_Resistor_triggered();
  void on_Capacitor_triggered();
  void on_Wire_triggered();
  void on_DragMode_triggered();
};
#endif  // MAINWINDOW_H
