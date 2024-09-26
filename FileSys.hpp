#pragma once
#include <QDebug>
#include <qchar.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <QTextStream>
#include <QRegularExpression>
class FileSystem : public QFileDialog {
 public:
  FileSystem(){}
  void OpenProj(QString proj);
 private:
  QFile CurrentFile;
};