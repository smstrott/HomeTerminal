#include "navigationwindow.h"

#include <QNetworkReply>


NavigationWindow::NavigationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    bnthm = new QPushButton(this);
    bnthm->setGeometry(0, 0, 240, 160);
    bnthm_icon.addFile(":/button_icons/return.svg");
    bnthm->setIcon(bnthm_icon);
    bnthm->setIconSize(QSize(160,160));

    bntDayFc = new QPushButton(this);
    bntDayFc->setGeometry(240, 0, 240, 160);
    bntDayFc_icon.addFile(":/button_icons/weather_day.png");
    bntDayFc->setIcon(bntDayFc_icon);
    bntDayFc->setIconSize(QSize(160,160));

    bntWeekFc = new QPushButton(this);
    bntWeekFc->setGeometry(0, 160, 240, 160);
    bntWeekFc_icon.addFile(":/button_icons/weather_week.svg");
    bntWeekFc->setIcon(bntWeekFc_icon);
    bntWeekFc->setIconSize(QSize(160,160));

    bntSmartHm = new QPushButton(this);
    bntSmartHm->setGeometry(240, 160, 240, 160);
    bntSmartHm_icon.addFile(":/button_icons/smarthome.png");
    bntSmartHm->setIcon(bntSmartHm_icon);
    bntSmartHm->setIconSize(QSize(160,160));

    fc_win = new ForecastWindow();
    fc_win->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    d_win = new DayliWindow();
    d_win->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    sh_win = new SmartHome();
    sh_win->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QObject::connect(bnthm, SIGNAL(clicked()), this, SLOT(push_bnthm()));
    QObject::connect(bntDayFc, SIGNAL(clicked()), this, SLOT(push_bntDayFc()));
    QObject::connect(bntWeekFc, SIGNAL(clicked()), this, SLOT(push_bntWeekFc()));
    QObject::connect(bntSmartHm, SIGNAL(clicked()), this, SLOT(push_bntSmartHm()));
}

void NavigationWindow::push_bnthm()
{
    this->hide();
}

void NavigationWindow::push_bntDayFc()
{
    d_win->showFullScreen();
    this->hide();
}

void NavigationWindow::push_bntWeekFc()
{
    fc_win->showFullScreen();
    this->hide();
}

void NavigationWindow::push_bntSmartHm()
{
    sh_win->showFullScreen();
    this->hide();
}

NavigationWindow::~NavigationWindow() {
}
