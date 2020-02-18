#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include <iostream>

class MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);

    w.show();
    
    return a.exec();
}
