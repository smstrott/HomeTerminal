#include "traffic.h"


traffic::traffic(QObject *parent) :
    QEventLoop(parent)
{
    traffic_timer = new QTimer(this);
    traffic_timer->start(30000);
    connect(traffic_timer, &QTimer::timeout, this, &traffic::refreshTraffic);
    connect(this, SIGNAL (traffic_Downloaded()), SLOT (loadCurrentTraffic()));
}

traffic::~traffic()
{

}

void traffic::init()
{
    QFile file;
    file.setFileName(":/Konfiguration.json");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(bytes);
    jsonObj = document.object();
    traffic_obj = jsonObj.value("traffic").toObject();
    accessId = traffic_obj.take("accessId").toString();
    id = traffic_obj.take("id").toString();
}

void traffic::refreshTraffic(){
    qInfo() << "BVG Weil wir dich refreshen";
    QDateTime timestamp;
    timestamp =QDateTime::currentDateTime();
    QString c_date=timestamp.toString("yyyy-MM-dd");
    QString c_time=timestamp.toString("hh:mm");
    QUrl BVG_url("https://vbb.demo.hafas.de/fahrinfo/restproxy/2.15/departureBoard?");
    //QUrl BVG_url("http://demo.hafas.de/openapi/vbb-proxy/departureBoard?");
    QUrlQuery BVG_query;
    BVG_query.addQueryItem("accessId", accessId);
    BVG_query.addQueryItem("id", id);
    BVG_query.addQueryItem("format", "json");
    BVG_query.addQueryItem("date", c_date);
    BVG_query.addQueryItem("time", c_time);
    BVG_url.setQuery(BVG_query);
    qInfo() << BVG_url;
    connect(&m_BVG_WebCtrl, SIGNAL (finished(QNetworkReply*)),
    SLOT (trafficDownloaded(QNetworkReply*)));
    QNetworkRequest BVG_request(BVG_url);
    m_BVG_WebCtrl.get(BVG_request);
}

void traffic::loadCurrentTraffic() {
    qInfo() << QDateTime::currentDateTime();
    qInfo() << "BVG Weil wir dich loaden";
    QJsonDocument BVG_document = QJsonDocument::fromJson(downloadedTraffic());
    qInfo() << "BVG Data was downloaded";
    //qInfo() << BVG_document;

    if (BVG_document.isObject()) {
        QJsonObject BVG_obj = BVG_document.object();
        QJsonObject BVG_tempObject;
        QJsonArray BVG_Array;
        QJsonArray BVG_tempArray;
        QJsonValue BVG_tempValue;
        QJsonValue BVG_Depature;
        QJsonValue tempString;
        qInfo() << "BVG_document is obviously an Object";
        BVG_Depature = BVG_obj.value(QStringLiteral("Departure"));
        BVG_Array = BVG_Depature.toArray();
        int keys = BVG_Array.size();
        qInfo() << "BVG Array Size: " << keys;
        for(int i =0;i<keys;i++){
            BVG_tempValue=BVG_Array.at(i);
            BVG_tempObject=BVG_tempValue.toObject();
            if(BVG_tempObject.contains(QStringLiteral("name"))){
                BVG_name[i]=BVG_tempObject.value(QStringLiteral("name")).toString();
            }
            if(BVG_tempObject.contains(QStringLiteral("direction"))){
                BVG_direction[i]=BVG_tempObject.value(QStringLiteral("direction")).toString();
            }
            if(BVG_tempObject.contains(QStringLiteral("time"))){
                QDateTime now=QDateTime::currentDateTime();
                BVG_date[i]=BVG_time[i]=BVG_tempObject.value(QStringLiteral("date")).toString();
                BVG_time[i]=BVG_tempObject.value(QStringLiteral("time")).toString();
                QDateTime then = QDateTime::fromString(BVG_date[i] + " " + BVG_time[i],"yyyy-MM-dd hh:mm:ss");
                int minutesTo = now.secsTo(then)/60;
                BVG_minutesTo[i]=QString::number(minutesTo);
            }
            if(BVG_tempObject.contains(QStringLiteral("Product"))){
                BVG_tempValue=BVG_tempObject.value(QStringLiteral("Product"));
                BVG_tempArray=BVG_tempValue.toArray();
                BVG_tempValue=BVG_tempArray.at(0);
                BVG_tempObject=BVG_tempValue.toObject();
                BVG_tempObject=BVG_tempObject.value(QStringLiteral("icon")).toObject();
                BVG_obj=BVG_tempObject.value(QStringLiteral("backgroundColor")).toObject();
                bgColor_r[i]=BVG_obj.value(QStringLiteral("r")).toInt();
                bgColor_g[i]=BVG_obj.value(QStringLiteral("g")).toInt();
                bgColor_b[i]=BVG_obj.value(QStringLiteral("b")).toInt();
                bgColor_hex[i]=BVG_obj.value(QStringLiteral("hex")).toString();
                BVG_obj=BVG_tempObject.value(QStringLiteral("foregroundColor")).toObject();
                fgColor_r[i]=BVG_obj.value(QStringLiteral("r")).toInt();
                fgColor_g[i]=BVG_obj.value(QStringLiteral("g")).toInt();
                fgColor_b[i]=BVG_obj.value(QStringLiteral("b")).toInt();
                fgColor_hex[i]=BVG_obj.value(QStringLiteral("hex")).toString();

            }
        }
    }
}

void traffic::trafficDownloaded(QNetworkReply* BVG_pReply)
{
    m_downloadedTraffic = BVG_pReply->readAll();
    //emit a signal
    BVG_pReply->deleteLater();
    emit traffic_Downloaded();
}

QByteArray traffic::downloadedTraffic() const
{
    return m_downloadedTraffic;
}
