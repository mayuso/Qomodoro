#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "TimerWindow.h"
#include "StatsWindow.h"

#include <QVBoxLayout>
#include <QShortcut>
#include <QDir>
#include <QTabBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet("background-color: #222; color: white");
    setWindowTitle("Qomodoro");
    setWindowIcon(QIcon(":/images/icon.png"));

    while(ui->tabWidget->count() > 0)
        ui->tabWidget->removeTab(0);

    TimerWindow* timerWindow = new TimerWindow();

    connect(timerWindow, &TimerWindow::sg_PomodoroFinished, this, &MainWindow::PomodoroFinished);

    ui->tabWidget->addTab(timerWindow, "Timer");
    ui->tabWidget->addTab(new StatsWindow(), "Stats");
    ui->tabWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PomodoroFinished()
{
    show();
    activateWindow();
    raise();
}
