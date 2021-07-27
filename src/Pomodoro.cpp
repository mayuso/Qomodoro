#include "Pomodoro.h"
#include "DataIO.h"

#include <fstream>
#include <sys/stat.h>
#include <ctime>

using json = nlohmann::json;

Pomodoro::Pomodoro(QObject *parent) :
    QObject(parent)
{
    m_TimeLeft = 0;
    m_IntervalMiliseconds = 50;
    m_Timer = new QTimer();
    m_Timer->setInterval(m_IntervalMiliseconds);
    m_Timer->setTimerType(Qt::PreciseTimer);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));

    m_PomodoroCounter = 1;
    m_IsPomodoroRunning = false;

    m_PomodoroDurationMinutes = 25;
    m_ShortBreakDurationMinutes = 5;
    m_LongBreakDurationMinutes = 20;
    m_CurrentTaskTime = m_PomodoroDurationMinutes;
    m_TimeLeft = m_PomodoroDurationMinutes * 60 * (1000 / m_IntervalMiliseconds);
}

Pomodoro::~Pomodoro()
{
    delete m_Timer;
}

void Pomodoro::StartPomodoro()
{
    m_IsPomodoroRunning = true;
    m_IsBreakRunning = false;
    m_Timer->stop();
    m_TimeLeft = m_PomodoroDurationMinutes * 60 * (1000 / m_IntervalMiliseconds);
    m_CurrentTaskTime = m_TimeLeft;
    m_Timer->start();
    emit sg_PomodoroStarted();
}

void Pomodoro::StartShortBreak()
{
    m_IsPomodoroRunning = false;
    m_IsBreakRunning = true;
    m_Timer->stop();
    m_TimeLeft = m_ShortBreakDurationMinutes * 60 * (1000 / m_IntervalMiliseconds);
    m_CurrentTaskTime = m_TimeLeft;
    m_Timer->start();
}

void Pomodoro::StartLongBreak()
{
    m_IsPomodoroRunning = false;
    m_IsBreakRunning = true;
    m_Timer->stop();
    m_TimeLeft = m_LongBreakDurationMinutes * 60 * (1000 / m_IntervalMiliseconds);
    m_CurrentTaskTime = m_TimeLeft;
    m_Timer->start();
}

void Pomodoro::Reset()
{
    m_IsPomodoroRunning = false;
    m_IsBreakRunning = false;
    m_Timer->stop();
    m_TimeLeft = m_PomodoroDurationMinutes * 60 * (1000 / m_IntervalMiliseconds);
    m_CurrentTaskTime = m_TimeLeft;
    emit sg_PomodoroFinished();
}

void Pomodoro::TimerTicked()
{
    m_TimeLeft--;
    emit sg_Tick();

    if (m_TimeLeft <= 0) {
        m_TimeLeft = 0;
        m_Timer->stop();

        if(m_IsPomodoroRunning)
        {


            std::time_t t = std::time(nullptr);   // get time now
            std::tm* now = std::localtime(&t);

            QString date = QString("%1").arg(now->tm_year + 1900, 2, 10, QChar('0')) + '-' + QString("%1").arg(now->tm_mon + 1, 2, 10, QChar('0')) + '-' + QString("%1").arg(now->tm_mday, 2, 10, QChar('0'));
            QString endTime = QString("%1").arg(now->tm_hour, 2, 10, QChar('0')) + ":" + QString("%1").arg(now->tm_min, 2, 10, QChar('0'));

            json newPomodoro = {
                json::object_t::value_type("end_time", endTime.toStdString()),
                json::object_t::value_type("date", date.toStdString()),
                json::object_t::value_type("duration", m_PomodoroDurationMinutes)
            };


            json jsonData = DataIO::LoadData();
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
            DataIO::SaveData(jsonData);

            emit sg_PomodoroFinished();
            StartBreak();
        }
        else
        {
            emit sg_BreakFinished();
        }
        emit sg_Timeout();
    }
}

void Pomodoro::StartBreak()
{
    m_IsPomodoroRunning = false;
    m_IsBreakRunning = true;
    m_PomodoroCounter += 1;
    if(m_PomodoroCounter < 5)
    {
        StartShortBreak();
    }
    else
    {
        m_PomodoroCounter = 0;
        StartLongBreak();
    }
    emit sg_BreakStarted();
}

int Pomodoro::GetLongBreakDurationMinutes() const
{
    return m_LongBreakDurationMinutes;
}

void Pomodoro::SetLongBreakDurationMinutes(int value)
{
    m_LongBreakDurationMinutes = value;
    if(!m_IsBreakRunning && !m_IsPomodoroRunning)
        m_TimeLeft = value * 60 * (1000 / m_IntervalMiliseconds);
}

int Pomodoro::GetShortBreakDurationMinutes() const
{
    return m_ShortBreakDurationMinutes;
}

void Pomodoro::SetShortBreakDurationMinutes(int value)
{
    m_ShortBreakDurationMinutes = value;
    if(!m_IsBreakRunning && !m_IsPomodoroRunning)
        m_TimeLeft = value * 60 * (1000 / m_IntervalMiliseconds);
}

int Pomodoro::GetPomodoroDurationMinutes() const
{
    return m_PomodoroDurationMinutes;
}

void Pomodoro::SetPomodoroDurationMinutes(int value)
{
    m_PomodoroDurationMinutes = value;
    if(!m_IsBreakRunning && !m_IsPomodoroRunning)
        m_TimeLeft = value * 60 * (1000 / m_IntervalMiliseconds);
}

int Pomodoro::GetTimeLeft()
{
    return m_TimeLeft;
}
int Pomodoro::GetCurrentTaskTime()
{
    return m_CurrentTaskTime;
}
