#include "mainwindow.h"
#include <QApplication>
#include <qstylefactory.h>
void setMode(QApplication&);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setMode(a);
    MainWindow w;
    w.show();
    return a.exec();
}

void setMode(QApplication& a) {
    // 设置浅色模式
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::AlternateBase, Qt::lightGray);
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, Qt::white);
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Link, Qt::blue);
    lightPalette.setColor(QPalette::Highlight, Qt::blue);
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(lightPalette);
    a.setStyle(QStyleFactory::create("Fusion"));
}