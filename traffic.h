
#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <QEventLoop>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTime>
#include <QTimer>
#include <qfile.h>

class traffic : public QEventLoop
{
    Q_OBJECT
public:
    explicit traffic(QObject *parent = nullptr);
    virtual ~traffic();
    QByteArray downloadedTraffic() const;
    QNetworkAccessManager m_BVG_WebCtrl;
    QByteArray m_downloadedTraffic;
    QTimer *traffic_timer;

    //Forecast Weather Data
    int fgColor_r[100];
    int fgColor_g[100];
    int fgColor_b[100];
    QString fgColor_hex[100];
    int bgColor_r[100];
    int bgColor_g[100];
    int bgColor_b[100];
    QString bgColor_hex[100];
    QString BVG_name[100];
    QString BVG_time[100];
    QString BVG_date[100];
    QString BVG_direction[100];
    QString BVG_minutesTo[100];
    void init();


public slots:
    void loadCurrentTraffic();
    void refreshTraffic();
    void trafficDownloaded(QNetworkReply* pReply);

private:

    QJsonObject jsonObj;
      QJsonObject traffic_obj;
      QString accessId;
      QString id;



private slots:



signals:
    void traffic_Downloaded();
};

#endif // TRAFFIC_H
