#include "FileSys.hpp"

#include <qchar.h>
#include <qevent.h>
#include <qnamespace.h>

void FileSystem::OpenProj(QString proj) {
  QDir dir(proj);
  QString target;
  auto fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QFileInfo &fileInfo : fileList) {
    if (!fileInfo.fileName().compare("target.toml", Qt::CaseInsensitive)) {
      target = fileInfo.filePath();
      break;
    }
  }
  // project existed
  if (!target.isEmpty()) {
    qDebug() << target;
    QFile file(target);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Cannot open file:";
      return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    QRegularExpression re(R"(add_executable\s*\(([^)]+)\))");
    auto match = re.match(content);
    if (match.hasMatch()) {
      auto matched_str = match.captured(1);
      qDebug() << "Extracted content:" << matched_str;
    }
  }
  return;
}