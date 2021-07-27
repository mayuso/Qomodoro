#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "../vendor/json/single_include/nlohmann/json.hpp"
#include <QWidget>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

    void LoadConfig();

public slots:
    void SetControlsEnabled(bool enabled);

    void SetPomodoroTime(int time);
    void SetShortBreakTime(int time);
    void SetLongBreakTime(int time);
    void ResetValues();


signals:
    void sg_PomodoroTimeChanged(int);
    void sg_ShortBreakTimeChanged(int);
    void sg_LongBreakTimeChanged(int);

private:
    Ui::OptionsWindow *ui;


};

#endif // OPTIONSWINDOW_H
