#include "smarthome.h"

SmartHome::SmartHome(QWidget *parent)
    : QMainWindow(parent)
{
    bnt_sh_hide = new QPushButton(this);
    bnt_sh_hide->setGeometry(0, 0, 50, 50);
    icon.addFile(":/button_icons/return.svg");
    bnt_sh_hide->setIcon(icon);
    bnt_sh_hide->setIconSize(QSize(50,50));
    QObject::connect(bnt_sh_hide, SIGNAL(clicked()), this, SLOT(push_sh_hide()));

    bnt_frbx = new QPushButton("FRITZ!BOX",this);
    bnt_frbx->setGeometry(0, 50, 100, 50);
    QObject::connect(bnt_frbx, SIGNAL(clicked()), this, SLOT(push_frbx()));
    connect(this, SIGNAL (Fritz_Downloaded()), SLOT (loadCurrentFritz()));


}

void SmartHome::push_sh_hide()
{
    this->hide();
}

void SmartHome::push_frbx()
{
}

void SmartHome::testhash()
{
}

void SmartHome::loadCurrentFritz()
{
}


void SmartHome::FritzDownloaded(QNetworkReply* Fritz_pReply)
{
}


QByteArray SmartHome::downloadedFritz() const
{
    return m_downloadedFritz;
}

SmartHome::~SmartHome() {
}
