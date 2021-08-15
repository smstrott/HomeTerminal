#ifndef NAVIGATIONWINDOW_H
#define NAVIGATIONWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "forecastwindow.h"
#include "dayliwindow.h"
#include "smarthome.h"

class NavigationWindow : public QMainWindow
{
    Q_OBJECT
public:
    NavigationWindow(QWidget *parent = nullptr);
    virtual ~NavigationWindow();

public slots:
    void push_bnthm();
    void push_bntDayFc();
    void push_bntWeekFc();
    void push_bntSmartHm();

private:
    QPushButton* bnthm;
    QIcon bnthm_icon;
    QPushButton* bntDayFc;
    QIcon bntDayFc_icon;
    QPushButton* bntWeekFc;
    QIcon bntWeekFc_icon;
    QPushButton* bntSmartHm;
    QIcon bntSmartHm_icon;
    ForecastWindow *fc_win;
    DayliWindow *d_win;
    SmartHome *sh_win;

private slots:

signals:

};

#endif // NAVIGATIONWINDOW_H
