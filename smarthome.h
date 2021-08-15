#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <QMainWindow>
#include <QPushButton>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <QUrl>
#include <QUrlQuery>
#include <QXmlStreamReader>
#include <QCryptographicHash>
#include <qpassworddigestor.h>
#include <QTextCodec>

class SmartHome : public QMainWindow
{
    Q_OBJECT

public:
    SmartHome(QWidget *parent = nullptr);
    virtual ~SmartHome();
    QByteArray downloadedFritz() const;
    QNetworkAccessManager m_Fritz_WebCtrl;
    QByteArray m_downloadedFritz;
    QPushButton* bnt_sh_hide;
    QPushButton* bnt_frbx;
    QUrl response_url;


public slots:
    void loadCurrentFritz();
    void FritzDownloaded(QNetworkReply* pReply);

private:
    QIcon icon;


private slots:
void push_sh_hide();
void push_frbx();
void testhash();
signals:
    void Fritz_Downloaded();

};

#endif // SMARTHOME_H
