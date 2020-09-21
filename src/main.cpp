#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include <iostream>

class MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window(nullptr);
    window.setWindowFlags(Qt::FramelessWindowHint);
    window.show();
    
    return a.exec();
}
