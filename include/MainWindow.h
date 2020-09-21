#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "TimeLabel.h"
#include "Pomodoro.h"
#include "TopBarTitle.h"

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

    Ui::MainWindow *ui;
public slots:
    void PomodoroFinished();

    void MinimizeButtonClicked();
    void MaximizeButtonClicked();
    void CloseButtonClicked();

private:
    TopBarTitle *m_TitleBar;

};

#endif // MAINWINDOW_H
