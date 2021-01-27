#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "Pomodoro.h"
#include "TopBarTitle.h"

#include "TimerWindow.h"
#include "StatsWindow.h"
#include "OptionsWindow.h"

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

    void OptionsButtonClicked();
    void StatsButtonClicked();
    void MinimizeButtonClicked();
    void CloseButtonClicked();

private:
    TopBarTitle *m_TitleBar;

    StatsWindow *m_StatsWindow;
    OptionsWindow *m_OptionsWindow;
    TimerWindow *m_TimerWindow;

};

#endif // MAINWINDOW_H
