#include "TimerWindow.h"
#include "ui_TimerWindow.h"
#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QDir>
#include <QPainterPath>

TimerWindow::TimerWindow(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::TimerWindow)
{
    ui->setupUi(this);

    m_Pomodoro = new Pomodoro(this);

    playPixmap = new QPixmap(":/images/play.png");
    stopPixmap = new QPixmap(":/images/stop.png");

    ui->pomodoroButton->setIconSize((*playPixmap).rect().size()/2);

    ui->pomodoroButton->setIcon(QIcon(*playPixmap));
    UpdateInfoLabel();
    UpdateTimeLabel();

    QFile styleFile( ":/stylesheets/TimerWindow.qss" );
    styleFile.open( QFile::ReadOnly );
    setStyleSheet( styleFile.readAll() );

    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);
    QList<QString> pomodoroNames;
    foreach(QString filename, pomodoroDataFiles) {
        pomodoroNames.append(filename.replace(".json", ""));
    }

    connect(ui->pomodoroButton, &QPushButton::clicked, this, &TimerWindow::PomodoroButtonClicked);

    connect(m_Pomodoro, &Pomodoro::sg_Tick, this, &TimerWindow::UpdateTime);
    connect(m_Pomodoro, &Pomodoro::sg_Timeout, this, &TimerWindow::TimeOut);
    connect(m_Pomodoro, &Pomodoro::sg_BreakFinished, this, &TimerWindow::BreakFinished);
    connect(m_Pomodoro, &Pomodoro::sg_PomodoroFinished, this, &TimerWindow::PomodoroFinished);
    connect(m_Pomodoro, &Pomodoro::sg_BreakStarted, this, &TimerWindow::BreakStarted);
    connect(m_Pomodoro, &Pomodoro::sg_PomodoroStarted, this, &TimerWindow::PomodoroStarted);

    updateProgress(1.0);

    SetCircularBarColor(new QColor("#fe4c4b"));
}

TimerWindow::~TimerWindow()
{
    delete ui;
}

void TimerWindow::SetCircularBarColor(QColor* m_Color)
{
    m_CircularBarColor = m_Color;
}

void TimerWindow::updateProgress(qreal newProgress) {
    if (m_Progress == newProgress) return;
    m_Progress = newProgress;
    update();
}

void TimerWindow::paintEvent(QPaintEvent *) {
    qreal pd = m_Progress * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
    p.fillRect(rect(), Qt::transparent);
    p.translate(90, 50);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path, path2;
    path.moveTo((this->width()-(this->width()*0.45))/2, 0);
    path.arcTo(QRectF(0, 0, this->width()-(this->width()*0.45), this->width()-(this->width()*0.45)), 90, -pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(*m_CircularBarColor);
    pen.setWidth(12);
    p.strokePath(path, pen);
    path2.moveTo((this->width()-(this->width()*0.45))/2, 0);
    pen2.setWidth(12);
    pen2.setColor(QColor("#232938"));
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setDashPattern(QVector<qreal>{2, 0});
    path2.arcTo(QRectF(0, 0, this->width()-(this->width()*0.45), this->width()-(this->width()*0.45)), 90, rd);
    pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);
}

void TimerWindow::SetPomodoroTime(int time)
{
    m_Pomodoro->SetPomodoroDurationMinutes(time);
    UpdateTimeLabel();
}

void TimerWindow::SetShortBreakTime(int time)
{
    m_Pomodoro->SetShortBreakDurationMinutes(time);
}

void TimerWindow::SetLongBreakTime(int time)
{
    m_Pomodoro->SetLongBreakDurationMinutes(time);
}

void TimerWindow::PomodoroFinished()
{
    SetCircularBarColor(new QColor("#fe4c4b"));
}

void TimerWindow::BreakFinished()
{
    SetCircularBarColor(new QColor("#fe4c4b"));
}
void TimerWindow::PomodoroStarted()
{
    SetCircularBarColor(new QColor("#fe4c4b"));
    UpdateInfoLabel();
}

void TimerWindow::BreakStarted()
{
    SetCircularBarColor(new QColor("#05eb8b"));
    UpdateInfoLabel();
}

void TimerWindow::TimeOut()
{
    ui->pomodoroButton->setIcon(QIcon(*playPixmap));
    emit sg_TimerFinished();
}

void TimerWindow::UpdateTime()
{
    updateProgress((qreal)m_Pomodoro->GetTimeLeft() / (qreal)m_Pomodoro->GetCurrentTaskTime());

    UpdateTimeLabel();
}

void TimerWindow::UpdateTimeLabel()
{
    int minutes = m_Pomodoro->GetTimeLeft() / (1000 * 60 / m_Pomodoro->m_IntervalMiliseconds);
    int seconds = m_Pomodoro->GetTimeLeft() / (1000 / m_Pomodoro->m_IntervalMiliseconds) - (minutes * 60);

    QString minutesString = QString::number(minutes);
    QString secondsString = QString::number(seconds);
    if(seconds < 10)
         secondsString = "0" + QString::number(seconds);

    ui->timerLabel->setText(minutesString + ":" + secondsString);
}

void TimerWindow::PomodoroButtonClicked()
{
    if(m_Pomodoro->m_IsPomodoroRunning)
    {
        ui->pomodoroButton->setIcon(QIcon(*playPixmap));
        Reset();
    }
    else
    {
        ui->pomodoroButton->setIcon(QIcon(*stopPixmap));
        StartPomodoro();
    }
}

void TimerWindow::StartPomodoro()
{
    m_Pomodoro->StartPomodoro();
}

void TimerWindow::Reset()
{
    m_Pomodoro->Reset();
    UpdateTime();
}

void TimerWindow::UpdateInfoLabel()
{
    if(m_Pomodoro->m_IsBreakRunning)
    {
        if(m_Pomodoro->m_PomodoroCounter == 0)
            ui->infoLabel->setText("Session Finished! Long Break");
        else
            ui->infoLabel->setText("Break");

    }
    else
    {
        ui->infoLabel->setText("Pomodoro: " + QString::number(m_Pomodoro->m_PomodoroCounter) + "/4");
    }


}
