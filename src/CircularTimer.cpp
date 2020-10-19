#include "CircularTimer.h"
#include "ui_CircularTimer.h"
#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QDir>
#include <QPainterPath>

CircularTimer::CircularTimer(QWidget * parent) :
    QWidget(parent),
    p(0),
    ui(new Ui::CircularTimer)
{
    ui->setupUi(this);

    QPixmap playPixmap(":/images/play.png");
    QPixmap stopPixamp(":/images/stop.png");

    ui->pomodoroButton->setIcon(QIcon(playPixmap));
    ui->resetButton->setIcon(QIcon(stopPixamp));

    ui->pomodoroButton->setIconSize(playPixmap.rect().size()/2);
    ui->resetButton->setIconSize(stopPixamp.rect().size()/2);

    QFile styleFile( ":/stylesheets/CircularTimer.qss" );
    styleFile.open( QFile::ReadOnly );
    setStyleSheet( styleFile.readAll() );

    m_Pomodoro = new Pomodoro(this);



    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);
    QList<QString> pomodoroNames;
    foreach(QString filename, pomodoroDataFiles) {
        pomodoroNames.append(filename.replace(".json", ""));
    }
    ui->pomodoroNameComboBox->addItems(pomodoroNames);
    ui->pomodoroNameComboBox->setEditText("");
    QAbstractItemModel* model = ui->pomodoroNameComboBox->model();
    for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
        QModelIndex index = model->index(i, 0);
        model->setData(index, QSize(50, 50), Qt::SizeHintRole);
    }

    connect(ui->pomodoroButton, &QPushButton::clicked, this, &CircularTimer::StartPomodoro);
    connect(ui->resetButton, &QPushButton::clicked, this, &CircularTimer::Reset);
    connect(ui->pomodoroNameComboBox, &QComboBox::currentTextChanged, this, &CircularTimer::PomodoroSelected);

    connect(m_Pomodoro, &Pomodoro::sg_Tick, this, &CircularTimer::UpdateTime);
    connect(m_Pomodoro, &Pomodoro::sg_Timeout, this, &CircularTimer::TimeOut);


    connect(m_Pomodoro, &Pomodoro::sg_BreakFinished, this, &CircularTimer::BreakFinished);
    connect(m_Pomodoro, &Pomodoro::sg_PomodoroFinished, this, &CircularTimer::PomodoroFinished);
    connect(m_Pomodoro, &Pomodoro::sg_BreakStarted, this, &CircularTimer::BreakStarted);
    connect(m_Pomodoro, &Pomodoro::sg_PomodoroStarted, this, &CircularTimer::PomodoroStarted);

    ui->resetButton->setEnabled(false);
    ui->pomodoroButton->setEnabled(ui->pomodoroNameComboBox->currentText() != QString(""));

    upd((qreal)m_Pomodoro->GetPomodoroDurationMinutes() / 60);


    SetCircularBarColor(new QColor("#C0C0C0"));

}

CircularTimer::~CircularTimer()
{
    delete ui;
}

void CircularTimer::SetCircularBarColor(QColor* m_Color)
{
    m_CircularBarColor = m_Color;
}

void CircularTimer::upd(qreal pp) {
    if (p == pp) return;
    p = pp;
    update();
}

void CircularTimer::paintEvent(QPaintEvent *) {
    qreal pd = p * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
    p.fillRect(rect(), Qt::transparent);
    p.translate(15, 15);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path, path2;
    path.moveTo((this->width()-(this->width()*0.04))/2, 0);
    path.arcTo(QRectF(0, 0, this->width()-(this->width()*0.04), this->width()-(this->width()*0.04)), 90, -pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(*m_CircularBarColor);
    pen.setWidth(12);
    p.strokePath(path, pen);
    path2.moveTo((this->width()-(this->width()*0.04))/2, 0);
    pen2.setWidth(12);
    pen2.setColor(QColor("#d7d7d7"));
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    path2.arcTo(QRectF(0, 0, this->width()-(this->width()*0.04), this->width()-(this->width()*0.04)), 90, rd);
    pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);
}

void CircularTimer::resizeEvent(QResizeEvent *event)
{
    event->accept();

    if(event->size().width() > event->size().height()){
        QWidget::resize(event->size().height(),event->size().height());
    }else{
        QWidget::resize(event->size().width(),event->size().width());
    }
}


void CircularTimer::PomodoroSelected(const QString& pomodoroName)
{
    m_Pomodoro->SetName(pomodoroName);

    ui->pomodoroButton->setEnabled(pomodoroName != QString(""));
}

void CircularTimer::SetPomodoroTime(int time)
{

    m_Pomodoro->SetPomodoroDurationMinutes(time);
    upd((qreal)m_Pomodoro->GetTimeLeft() / 3600);
    //ui->timeLabel->SetTime(m_Pomodoro->GetTimeLeft(), true);
}

void CircularTimer::SetShortBreakTime(int time)
{
    m_Pomodoro->SetShortBreakDurationMinutes(time);
}

void CircularTimer::SetLongBreakTime(int time)
{
    m_Pomodoro->SetLongBreakDurationMinutes(time);
}

void CircularTimer::PomodoroFinished()
{
    SetCircularBarColor(new QColor("#C0C0C0"));
}

void CircularTimer::BreakFinished()
{
    SetCircularBarColor(new QColor("#C0C0C0"));
}
void CircularTimer::PomodoroStarted()
{
    SetCircularBarColor(new QColor("#30b7e0"));
}

void CircularTimer::BreakStarted()
{
    SetCircularBarColor(new QColor("#00ff1f"));
}

void CircularTimer::TimeOut()
{
    ui->pomodoroButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
    ui->pomodoroNameComboBox->setEnabled(true);
    emit sg_TimerFinished();
}

void CircularTimer::UpdateTime()
{

    upd((qreal)m_Pomodoro->GetTimeLeft() / 3600);
}

void CircularTimer::StartPomodoro()
{
    ui->pomodoroButton->setEnabled(false);
    ui->resetButton->setEnabled(true);
    ui->pomodoroNameComboBox->setEnabled(false);
    m_Pomodoro->StartPomodoro();
    ui->statusLabel->setText("");
}

void CircularTimer::Reset()
{
    ui->pomodoroButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
    ui->pomodoroNameComboBox->setEnabled(true);
    m_Pomodoro->Reset();
    upd((qreal)m_Pomodoro->GetTimeLeft() / 3600);
    ui->statusLabel->setText("");
}
