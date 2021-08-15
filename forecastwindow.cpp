#include "forecastwindow.h"

ForecastWindow::ForecastWindow(QWidget *parent)
    : QMainWindow(parent)
{
    bnthm = new QPushButton(this);
    bnthm->setGeometry(0, 0, 50, 50);
    icon.addFile(":/button_icons/return.svg");
    bnthm->setIcon(icon);
    bnthm->setIconSize(QSize(50,50));

    QObject::connect(bnthm, SIGNAL(clicked()), this, SLOT(bnt_fc_hide()));
}

void ForecastWindow::bnt_fc_hide()
{
    this->hide();
}

ForecastWindow::~ForecastWindow() {
}
