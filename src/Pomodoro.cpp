#include "Pomodoro.h"
#include <fstream>
#include <sys/stat.h>
#include <ctime>

using json = nlohmann::json;

#include <QDir>

Pomodoro::Pomodoro(QObject *parent) :
    QObject(parent)
{
    name = "";
    time_left = 0;
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));

    pomodoroCounter = 0;
    isPomodoroRunning = false;

    pomodoroDurationMinutes = 25;
    shortBreakDurationMinutes = 5;
    longBreakDurationMinutes = 20;
}

Pomodoro::~Pomodoro()
{
    delete timer;
}

void Pomodoro::startPomodoro()
{
    isPomodoroRunning = true;
    timer->stop();
    time_left = pomodoroDurationMinutes * 60;
    timer->start();
}

void Pomodoro::startShortBreak()
{
    isPomodoroRunning = false;
    timer->stop();
    time_left = shortBreakDurationMinutes * 60;
    timer->start();
}

void Pomodoro::startLongBreak()
{
    isPomodoroRunning = false;
    timer->stop();
    time_left = longBreakDurationMinutes * 60;
    timer->start();
}

void Pomodoro::pause()
{
    timer->stop();
}

void Pomodoro::resume()
{
    timer->start();
}


void Pomodoro::timerTicked()
{
    time_left--;
    emit tick(isPomodoroRunning);
    if (time_left <= 0) {
        time_left = 0;
        timer->stop();

        if(isPomodoroRunning)
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
                json::object_t::value_type("duration", pomodoroDurationMinutes)
            };

            std::ifstream ifs("./data/" + name.toStdString() + ".json");
            try
            {
                // APPEND TO THE EXISTING LIST
                jsonData = json::parse(ifs);
                jsonData += newPomodoro;
            }
            catch (json::exception& e)
            {
                // CREATE NEW DATA STRUCTURE
                jsonData = {newPomodoro};
            }
            ifs.close();
            std::ofstream myfile;
            myfile.open ("./data/" + name.toStdString() + ".json");
            myfile << jsonData;
            myfile.close();

            pomodoroCounter += 1;
            if(pomodoroCounter < 4)
            {
                startShortBreak();
            }
            else
            {
                pomodoroCounter = 0;
                startLongBreak();
            }

            emit timeout();
        }

    }
}

int Pomodoro::GetLongBreakDurationMinutes() const
{
    return longBreakDurationMinutes;
}

void Pomodoro::SetLongBreakDurationMinutes(int value)
{
    longBreakDurationMinutes = value;
}

int Pomodoro::GetShortBreakDurationMinutes() const
{
    return shortBreakDurationMinutes;
}

void Pomodoro::SetShortBreakDurationMinutes(int value)
{
    shortBreakDurationMinutes = value;
}

int Pomodoro::GetPomodoroDurationMinutes() const
{
    return pomodoroDurationMinutes;
}

void Pomodoro::SetPomodoroDurationMinutes(int value)
{
    pomodoroDurationMinutes = value;
}

QString Pomodoro::GetName() const
{
    return name;
}

void Pomodoro::SetName(const QString &value)
{
    name = value;
}

time_t Pomodoro::getTimeLeft()
{
    return time_left;
}

bool Pomodoro::isActive()
{
    return timer->isActive();
}
