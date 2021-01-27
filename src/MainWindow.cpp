#include "MainWindow.h"
#include "ui_MainWindow.h"

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
    setStyleSheet( styleFile.readAll() );

    m_TitleBar = new TopBarTitle(this);
    ui->topBarLayout->insertWidget(1, m_TitleBar);

    connect(ui->minButton, &QPushButton::clicked, this, &MainWindow::MinimizeButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::CloseButtonClicked);


    m_TimerWindow = new TimerWindow();
    connect(m_TimerWindow, &TimerWindow::sg_TimerFinished, this, &MainWindow::TimerFinished);

    m_OptionsWindow = new OptionsWindow();
    m_StatsWindow = new StatsWindow();

    connect(m_OptionsWindow, SIGNAL(sg_PomodoroTimeChanged(int)), m_TimerWindow, SLOT(SetPomodoroTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_ShortBreakTimeChanged(int)), m_TimerWindow, SLOT(SetShortBreakTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_LongBreakTimeChanged(int)), m_TimerWindow, SLOT(SetLongBreakTime(int)));


    ui->slidingStackedWidget->addWidget(m_OptionsWindow);
    ui->slidingStackedWidget->addWidget(m_TimerWindow);
    ui->slidingStackedWidget->addWidget(m_StatsWindow);
    ui->slidingStackedWidget->setCurrentIndex(1);

    ui->slidingStackedWidget->setSpeed(750);

    connect(ui->optionsButton, &QPushButton::clicked, this, &MainWindow::OptionsButtonClicked);
    connect(m_TimerWindow->GetStatsButton(), &QPushButton::clicked, this, &MainWindow::StatsButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerFinished()
{
    show();
    activateWindow();
    raise();
}

void MainWindow::OptionsButtonClicked()
{
    if(ui->slidingStackedWidget->currentIndex() != 0)
    {
        ui->slidingStackedWidget->slideInIdx(0);
    }
    else
    {
        ui->slidingStackedWidget->slideInIdx(1);
    }
}

void MainWindow::StatsButtonClicked()
{
    if(ui->slidingStackedWidget->currentIndex() != 2)
    {
        ui->slidingStackedWidget->slideInIdx(2);
    }
    else
    {
        ui->slidingStackedWidget->slideInIdx(1);
    }
}

void MainWindow::MinimizeButtonClicked()
{
    showMinimized();
}
void MainWindow::CloseButtonClicked()
{
    close();
}
