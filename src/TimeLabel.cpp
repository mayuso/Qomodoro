#include "TimeLabel.h"

TimeLabel::TimeLabel(QWidget *parent) :
    QLabel(parent)
{
    font = new QFont("Courier New");
    font->setItalic(true);
    font->setPixelSize(72);
    setFont(*font);
}

TimeLabel::~TimeLabel()
{
    delete(font);
}

QString TimeLabel::formatTime(time_t seconds)
{
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

void TimeLabel::setTime(time_t time, bool isPomodoroRunning)
{
    QString text = "";
    if(!isPomodoroRunning)
        text = "Break: ";

    QLabel::setText(text + formatTime(time));
}

void TimeLabel::setText(const QString& text)
{
    QLabel::setText(text);
}
