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
    ui->topBarLayout->insertWidget(0, m_TitleBar);

    connect(ui->minButton, &QPushButton::clicked, this, &MainWindow::MinimizeButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::CloseButtonClicked);

    m_TimerWindow = new TimerWindow();
    connect(m_TimerWindow, &TimerWindow::sg_TimerFinished, this, &MainWindow::TimerFinished);

    m_OptionsWindow = new OptionsWindow();
    m_StatsWindow = new StatsWindow();

    connect(m_OptionsWindow, SIGNAL(sg_PomodoroTimeChanged(int)), m_TimerWindow, SLOT(SetPomodoroTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_ShortBreakTimeChanged(int)), m_TimerWindow, SLOT(SetShortBreakTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_LongBreakTimeChanged(int)), m_TimerWindow, SLOT(SetLongBreakTime(int)));

    m_OptionsWindow->LoadConfig();

    ui->slidingStackedWidget->addWidget(m_OptionsWindow);
    ui->slidingStackedWidget->addWidget(m_TimerWindow);
    ui->slidingStackedWidget->addWidget(m_StatsWindow);
    ui->slidingStackedWidget->setCurrentIndex(1);

    ui->slidingStackedWidget->setSpeed(650);

    connect(ui->optionsButton, &QPushButton::clicked, this, &MainWindow::BottomBarButtonClicked);
    connect(ui->timerButton, &QPushButton::clicked, this, &MainWindow::BottomBarButtonClicked);
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::BottomBarButtonClicked);

    QDir* dir = new QDir();
    dir->mkdir("data");
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

void MainWindow::BottomBarButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton *>(sender());
    if(clickedButton->objectName() == "optionsButton")
    {
        ui->slidingStackedWidget->slideInIdx(0);
    }
    else if(clickedButton->objectName() == "timerButton")
    {
        ui->slidingStackedWidget->slideInIdx(1);
    }
    else if(clickedButton->objectName() == "statsButton")
    {
        ui->slidingStackedWidget->slideInIdx(2);
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
