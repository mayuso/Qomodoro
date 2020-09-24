#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
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
    void TimerFinished();

    void MinimizeButtonClicked();
    void MaximizeButtonClicked();
    void CloseButtonClicked();

private:
    TopBarTitle *m_TitleBar;

};

#endif // MAINWINDOW_H
