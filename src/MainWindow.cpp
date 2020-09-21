#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TimerWindow.h"
#include "StatsWindow.h"

#include <QVBoxLayout>
#include <QShortcut>
#include <QDir>
#include <QTabBar>
#include <QSizeGrip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qomodoro");
    setWindowIcon(QIcon(":/images/icon.png"));

    QFile styleFile( ":/stylesheets/MainWindow.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    setStyleSheet( styleFile.readAll() );

    m_TitleBar = new TopBarTitle(this);
    ui->topBarLayout->insertWidget(0, m_TitleBar);

    connect(ui->minButton, &QPushButton::clicked, this, &MainWindow::MinimizeButtonClicked);
    connect(ui->maxButton, &QPushButton::clicked, this, &MainWindow::MaximizeButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::CloseButtonClicked);

    QSizeGrip *sizegrip = new QSizeGrip(this);
    ui->mainLayout->addWidget(sizegrip, 0, Qt::AlignRight | Qt::AlignBottom);

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


void MainWindow::MinimizeButtonClicked()
{
    showMinimized();
}
void MainWindow::MaximizeButtonClicked()
{
    if(isMaximized())
        showNormal();
    else
        showMaximized();
}
void MainWindow::CloseButtonClicked()
{

    close();
}
