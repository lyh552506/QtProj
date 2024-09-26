#include "mainwindow.h"

#include <qchar.h>
#include <qdir.h>
#include <qmenu.h>

#include "FileSys.hpp"


template <>
QMenu *MainWindow::get<QMenu>(std::string name) {
  if (Menus.find(name) == Menus.end())
    Menus[name] = menuBar()->addMenu(QString::fromStdString(name));
  return Menus[name];
}

template <>
QToolBar *MainWindow::get<QToolBar>(std::string name) {
  if (ToolBars.find(name) == ToolBars.end())
    ToolBars[name] = new QToolBar(QString::fromStdString(name), this);
  return ToolBars[name];
}

template <>
QAction *MainWindow::get<QAction>(std::string name) {
  if (Actions.find(name) == Actions.end())
    Actions[name] = new QAction(QString::fromStdString(name), this);
  return Actions[name];
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  file_sys = new FileSystem();
  InitToolBar();
  InitGraph();
}

MainWindow::~MainWindow() {}

void MainWindow::InitToolBar() {
  // clang-format off
  addActionShowToolBar<QMenu>("ToolBar","Put tool","Put");
    addActionWith<QToolBar>("Put","Mode",&MainWindow::on_DragMode_triggered);
    addActionWith<QToolBar>("Put","Resistor",&MainWindow::on_Resistor_triggered);
    addActionWith<QToolBar>("Put","Wire",&MainWindow::on_Wire_triggered);
  
  addActionShowToolBar<QMenu>("ToolBar","File tool","File");
    addActionWith<QToolBar>("File","File",&MainWindow::on_file_triggered);
    get<QToolBar>("File")->setVisible(false);
  
  addActionWith<QMenu>("File","Open",&MainWindow::onOpenProjClicked);
  addActionWith<QMenu>("File","Save",&MainWindow::save_file_triggered);
  
  this->addToolBar(Qt::LeftToolBarArea, get<QToolBar>("Put"));
  this->addToolBar(Qt::LeftToolBarArea, get<QToolBar>("File"));
  // clang-format on
  resize(1000, 800);
}
void MainWindow::showToolBar(QToolBar *toolBar) {
  foreach (QToolBar *bar, findChildren<QToolBar *>()) {
    bar->setVisible(bar == toolBar);
  }
}

void MainWindow::InitGraph() {
  scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 800, 600);
  view = new GraphicsView(scene, this);
  setCentralWidget(view);
}

void MainWindow::open_file_triggered() {
  qDebug() << "Open Test";
  auto file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"), "",
      tr("TIFF Files (*.tif *.tiff);;All Files (*)"));
  if (!file_name.isEmpty()) {
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
      QDataStream in(&file);
      scene->clear();  // 清空现有场景
      while (!in.atEnd()) {
        componentType ty;
        QPointF pos;
        // in >> ty;
        in >> pos;
        if (ty == _Resistor) {
          Resistor *resistor = new Resistor();
          resistor->setPos(pos);
          scene->addItem(resistor);
        }
      }
      file.close();
    }
  }
}

void MainWindow::save_file_triggered() {
  auto file_name = QFileDialog::getSaveFileName(
      this, tr("Save File"), "",
      tr("TIFF Files (*.tif *.tiff);;All Files (*)"));
  qDebug() << "Save Test" << file_name;
  if (!file_name.isEmpty()) {
    // 保存图形的基本信息
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly)) {
      QDataStream out(&file);
      // 遍历场景中的每个项并保存其信息
      for (auto item : scene->items()) {
        if (auto resistor = dynamic_cast<Resistor *>(item)) {
          out << _Resistor;
          out << resistor->pos();
        }
      }
      file.close();
    }
  }
}

void MainWindow::onOpenProjClicked() {
  auto dir_name = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir_name.isEmpty()) {
    file_sys->OpenProj(dir_name);
  }
}

void MainWindow::on_file_triggered() { qDebug() << "Test file"; }
void MainWindow::on_Resistor_triggered() { view->placeResistor(); }
void MainWindow::on_Capacitor_triggered() { view->placeCapacitor(); }
void MainWindow::on_Wire_triggered() { view->placeWire(); }
void MainWindow::on_DragMode_triggered() { view->changemode(); }