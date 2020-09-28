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
    connect(ui->maxButton, &QPushButton::clicked, this, &MainWindow::MaximizeButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::CloseButtonClicked);

    QSizeGrip *sizegrip = new QSizeGrip(this);
    ui->mainLayout->addWidget(sizegrip, 0, Qt::AlignRight | Qt::AlignBottom);

    while(ui->tabWidget->count() > 0)
        ui->tabWidget->removeTab(0);

    m_CircularTimer = new CircularTimer;
    connect(m_CircularTimer, &CircularTimer::sg_TimerFinished, this, &MainWindow::TimerFinished);


    m_StatsWindow = new StatsWindow();
    m_OptionsWindow = new OptionsWindow();

    //connect(m_CircularTimer, SIGNAL(sg_EnableOptionControls(bool)), m_OptionsWindow, SLOT(SetControlsEnabled(bool)));
    connect(m_OptionsWindow, SIGNAL(sg_PomodoroTimeChanged(int)), m_CircularTimer, SLOT(SetPomodoroTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_ShortBreakTimeChanged(int)), m_CircularTimer, SLOT(SetShortBreakTime(int)));
    connect(m_OptionsWindow, SIGNAL(sg_LongBreakTimeChanged(int)), m_CircularTimer, SLOT(SetLongBreakTime(int)));

    ui->tabWidget->addTab(m_CircularTimer, "Timer");
    ui->tabWidget->addTab(m_StatsWindow, "Stats");
    ui->tabWidget->addTab(m_OptionsWindow, "Options");
    ui->tabWidget->setCurrentIndex(0);
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
