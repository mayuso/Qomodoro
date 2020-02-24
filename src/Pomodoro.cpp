#include "Pomodoro.h"
#include "DataIO.h"

#include <fstream>
#include <sys/stat.h>
#include <ctime>
#include <QDir>

using json = nlohmann::json;

Pomodoro::Pomodoro(QObject *parent) :
    QObject(parent)
{
    m_Name = "";
    m_TimeLeft = 0;
    m_Timer = new QTimer();
    m_Timer->setInterval(1000);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));

    m_PomodoroCounter = 0;
    m_IsPomodoroRunning = false;

    m_PomodoroDurationMinutes = 25;
    m_ShortBreakDurationMinutes = 5;
    m_LongBreakDurationMinutes = 20;
}

Pomodoro::~Pomodoro()
{
    delete m_Timer;
}

void Pomodoro::StartPomodoro()
{
    m_IsPomodoroRunning = true;
    m_Timer->stop();
    m_TimeLeft = m_PomodoroDurationMinutes * 60;
    m_Timer->start();
}

void Pomodoro::StartShortBreak()
{
    m_IsPomodoroRunning = false;
    m_Timer->stop();
    m_TimeLeft = m_ShortBreakDurationMinutes * 60;
    m_Timer->start();
}

void Pomodoro::StartLongBreak()
{
    m_IsPomodoroRunning = false;
    m_Timer->stop();
    m_TimeLeft = m_LongBreakDurationMinutes * 60;
    m_Timer->start();
}

void Pomodoro::Reset()
{
    m_Timer->stop();
    m_TimeLeft = m_PomodoroDurationMinutes * 60;
}

void Pomodoro::TimerTicked()
{
    m_TimeLeft--;
    emit sg_Tick(m_IsPomodoroRunning);
    if (m_TimeLeft <= 0) {
        m_TimeLeft = 0;
        m_Timer->stop();

        if(m_IsPomodoroRunning)
        {
            QDir* dir = new QDir();

            dir->mkdir("data");

            std::time_t t = std::time(nullptr);   // get time now
            std::tm* now = std::localtime(&t);

            QString date = QString("%1").arg(now->tm_year + 1900, 2, 10, QChar('0')) + '-' + QString("%1").arg(now->tm_mon + 1, 2, 10, QChar('0')) + '-' + QString("%1").arg(now->tm_mday, 2, 10, QChar('0'));
            QString endTime = QString("%1").arg(now->tm_hour, 2, 10, QChar('0')) + ":" + QString("%1").arg(now->tm_min, 2, 10, QChar('0'));

            json newPomodoro = {
                json::object_t::value_type("end_time", endTime.toStdString()),
                json::object_t::value_type("date", date.toStdString()),
                json::object_t::value_type("duration", m_PomodoroDurationMinutes)
            };


            json jsonData = DataIO::LoadConfig(m_Name.toStdString());
            if(jsonData.size() > 0)
            {
                // Append new entry to the existing list
                jsonData += newPomodoro;
            }
            else
            {
                // Create new entry in the empty file
                jsonData = {newPomodoro};
            }
            DataIO::SaveConfig(jsonData, m_Name.toStdString());

            StartBreak();

            emit sg_Timeout();
        }
    }
}

void Pomodoro::StartBreak()
{
    m_PomodoroCounter += 1;
    if(m_PomodoroCounter < 4)
    {
        StartShortBreak();
    }
    else
    {
        m_PomodoroCounter = 0;
        StartLongBreak();
    }
}

int Pomodoro::GetLongBreakDurationMinutes() const
{
    return m_LongBreakDurationMinutes;
}

void Pomodoro::SetLongBreakDurationMinutes(int value)
{
    m_LongBreakDurationMinutes = value;
}

int Pomodoro::GetShortBreakDurationMinutes() const
{
    return m_ShortBreakDurationMinutes;
}

void Pomodoro::SetShortBreakDurationMinutes(int value)
{
    m_ShortBreakDurationMinutes = value;
}

int Pomodoro::GetPomodoroDurationMinutes() const
{
    return m_PomodoroDurationMinutes;
}

void Pomodoro::SetPomodoroDurationMinutes(int value)
{
    m_PomodoroDurationMinutes = value;
    m_TimeLeft = value * 60;
}

QString Pomodoro::GetName() const
{
    return m_Name;
}

void Pomodoro::SetName(const QString &value)
{
    m_Name = value;
}

time_t Pomodoro::GetTimeLeft()
{
    return m_TimeLeft;
}

bool Pomodoro::IsActive()
{
    return m_Timer->isActive();
}
