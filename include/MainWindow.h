#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "TimeLabel.h"
#include "Pomodoro.h"

class MainWindowPresenter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void PomodoroFinished();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
