#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  InitToolBar();
  InitGraph();
}

MainWindow::~MainWindow() {}

void MainWindow::InitToolBar() {
  menuToolBar = menuBar()->addMenu(tr("&ToolBar"));
  menuTest_put = menuBar()->addMenu(tr("&Put"));
  menuTest_file = menuBar()->addMenu(tr("&File"));

  toolBar_put = new QToolBar(tr("&put"), this);
  toolBar_file = new QToolBar(tr("&file"), this);

  actionTest_put = new QAction(tr("&Put tool"), this);
  actionTest_file = new QAction(tr("&File tool"), this);
  action_Open = new QAction(tr("&Open"), this);
  action_Save = new QAction(tr("&Save"), this);
  action_Resistor = new QAction(tr("&Resistor"), this);

  // add ToolBar act
  menuToolBar->addAction(actionTest_put);
  menuToolBar->addAction(actionTest_file);
  // add File act
  menuTest_file->addAction(action_Open);
  menuTest_file->addAction(action_Save);

  put = new QAction(tr("Put"), this);
  file = new QAction(tr("File"), this);
  toolBar_put->addAction(put);
  toolBar_file->addAction(file);
  toolBar_put->addAction(action_Resistor);
  // bind Put and File bar
  connect(actionTest_put, &QAction::triggered, this,
          [=]() { this->showToolBar(toolBar_put); });
  connect(actionTest_file, &QAction::triggered, this,
          [=]() { this->showToolBar(toolBar_file); });

  connect(action_Resistor, &QAction::triggered, this,
          &MainWindow::on_Resistor_triggered);

  // bind open and save bar
  connect(action_Open, &QAction::triggered, this,
          &MainWindow::open_file_triggered);
  connect(action_Save, &QAction::triggered, this,
          &MainWindow::save_file_triggered);

  connect(put, &QAction::triggered, this, &MainWindow::on_put_triggered);
  connect(file, &QAction::triggered, this, &MainWindow::on_file_triggered);

  this->addToolBar(Qt::LeftToolBarArea, toolBar_put);
  this->addToolBar(Qt::LeftToolBarArea, toolBar_file);

  resize(1000, 800);
}
void MainWindow::showToolBar(QToolBar *toolBar) {
  foreach (QToolBar *bar, findChildren<QToolBar *>()) {
    bar->setVisible(bar == toolBar);
  }
}

void MainWindow::InitGraph() {
  scene = new QGraphicsScene(this);
  scene->setSceneRect(-400, -300, 400, 300);
  view = new GraphicsView(scene, this);

  setCentralWidget(view);
}

void MainWindow::on_put_triggered() {
  qDebug() << "Test put";
  Resistor *item = new Resistor();
  scene->addItem(item);
  item->setPos(QPointF(100, 100));
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

void MainWindow::on_file_triggered() { qDebug() << "Test file"; }

void MainWindow::on_Resistor_triggered() { view->placeResistor(); }
void MainWindow::on_Capacitor_triggered() { view->placeCapacitor(); }
void MainWindow::on_Wire_triggered() { view->placeWire(); }