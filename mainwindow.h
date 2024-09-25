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
  std::unordered_map<std::string,QMenu*> Menus;
  std::unordered_map<std::string,QToolBar*> ToolBars;
  std::unordered_map<std::string,QAction*> Actions;
  template <typename T>
  T* get(std::string);
  
  template <typename T>
  void addAction(std::string Tname, std::string ActionName){
    auto action = get<QAction>(ActionName);
    get<T>(Tname)->addAction(action);
  }

  template <typename T>
  void addActionWith(std::string Tname,std::string ActionName,void (MainWindow::*&&slot)()){
    auto action = get<QAction>(ActionName);
    connect(action,&QAction::triggered,this,slot);
    get<T>(Tname)->addAction(action);
  }

  template <typename T>
  void addActionShowToolBar(std::string Tname,std::string ActionName,std::string ToolBarName){
    auto action = get<QAction>(ActionName);
    get<T>(Tname)->addAction(action);
    connect(action,&QAction::triggered,this,[=](){
      showToolBar(get<QToolBar>(ToolBarName));
    });
  }

  QGraphicsScene* scene;
  GraphicsView* view;

  QString current_file;
 private slots:
  void on_put_triggered();
  void on_file_triggered();
  void on_Resistor_triggered();
  void on_Capacitor_triggered();
  void on_Wire_triggered();
  void open_file_triggered();
  void save_file_triggered();
};
#endif  // MAINWINDOW_H
