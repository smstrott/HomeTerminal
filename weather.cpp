#include "weather.h"
#include "mainwindow.h"
#define ZERO_KELVIN 273.15
// example api call "api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=a9a98c5f3e757d9e21d7e0cd9282f518"
weather::weather(QObject *parent) :
    QEventLoop(parent)
{
    wc_timer = new QTimer(this);
    wf_timer = new QTimer(this);
    wc_timer->start(600000);
    wf_timer->start(1200000);
    connect(wc_timer, &QTimer::timeout, this, &weather::refreshCurrentWeather);
    connect(wf_timer, &QTimer::timeout, this, &weather::refreshForecastWeather);
    connect(this, SIGNAL (downloaded()), SLOT (loadCurrentWeather()));
    connect(this, SIGNAL (forecastdownloaded()), SLOT (loadForecastWeather()));
}

weather::~weather()
{

}


void weather::init()
{
    QFile file;
    file.setFileName(":/Konfiguration.json");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(bytes);
    jsonObj = document.object();
    weather_obj = jsonObj.value("weather").toObject();
    AppId = weather_obj.take("APPID").toString();
    City = weather_obj.take("city").toString();
    lat = weather_obj.take("lat").toString();
    lon = weather_obj.take("lon").toString();
}


void weather::refreshForecastWeather() {
    qInfo() << "refresh Forecast Weather";
    QUrl url("http://api.openweathermap.org/data/2.5/onecall");
    QUrlQuery query;
    query.addQueryItem("lat", lat);
    query.addQueryItem("lon", lon);
    query.addQueryItem("exclude", "minutely, hourly, alerts");
    query.addQueryItem("mode", "json");
    query.addQueryItem("APPID", AppId);
    url.setQuery(query);
    qInfo() << "ForecastURL: " << url;
    connect(&m_forecase_WebCtrl, SIGNAL (finished(QNetworkReply*)),
    SLOT (forecastfileDownloaded(QNetworkReply*)));
    QNetworkRequest request(url);
    m_forecase_WebCtrl.get(request);
}

void weather::refreshCurrentWeather(){
    qInfo() << "refresh Current Weather";
    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;
    query.addQueryItem("q", City);
    query.addQueryItem("mode", "json");
    query.addQueryItem("APPID", AppId);
    url.setQuery(query);
    qInfo() << "CurrentURL: " << url;
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
    SLOT (fileDownloaded(QNetworkReply*)));
    QNetworkRequest request(url);
    m_WebCtrl.get(request);
}

void weather::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
}

void weather::forecastfileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit forecastdownloaded();
}

QByteArray weather::downloadedData() const
{
    return m_DownloadedData;
}

static QString niceTemperatureString(double t)
{
    return QString::number(qRound(t-ZERO_KELVIN)) + QChar(0xB0);
}

void weather::loadCurrentWeather() {
    qInfo() << QDateTime::currentDateTime();
    qInfo() << "Current Weather";
    QJsonDocument document = QJsonDocument::fromJson(downloadedData());
    qInfo() << "Current Weather was downloaded";
    //qInfo() << document;

    if (document.isObject()) {
        QJsonObject obj = document.object();
        QJsonObject tempObject;
        QJsonArray tempArray;
        QJsonValue tempString;
        QJsonValue val;

        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            val = tempObject.value(QStringLiteral("temp"));
            //d->now.setTemperature(niceTemperatureString(val.toDouble()));
        }
        if (obj.contains(QStringLiteral("clouds"))) {
            val = obj.value(QStringLiteral("clouds"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("all"));
            wc_clouds_all = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("cod"))) {
            val = obj.value(QStringLiteral("cod"));
            wc_cod = val.toDouble();
        }
        if (obj.contains(QStringLiteral("coord"))) {
            val = obj.value(QStringLiteral("coord"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("lat"));
            wc_coord_lat = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("coord"))) {
            val = obj.value(QStringLiteral("coord"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("lat"));
            wc_coord_lon = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("coord"))) {
            val = obj.value(QStringLiteral("coord"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("lon"));
            wc_coord_lon = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("base"))) {
            val = obj.value(QStringLiteral("base"));
            wc_base = val.toString();
        }
        if (obj.contains(QStringLiteral("dt"))) {
            val = obj.value(QStringLiteral("dt"));
            wc_dt = val.toDouble();
        }
        if (obj.contains(QStringLiteral("id"))) {
            val = obj.value(QStringLiteral("id"));
            wc_id = val.toDouble();
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("feels_like"));
            wc_main_feels_like = niceTemperatureString(tempString.toDouble());
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("humidity"));
            wc_main_humidity = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("pressure"));
            wc_main_pressure = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("temp"));
            wc_main_temp = niceTemperatureString(tempString.toDouble());
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("temp_max"));
            wc_main_temp_max = niceTemperatureString(tempString.toDouble());
        }
        if (obj.contains(QStringLiteral("main"))) {
            val = obj.value(QStringLiteral("main"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("temp_min"));
            wc_main_temp_min = niceTemperatureString(tempString.toDouble());
        }
        if (obj.contains(QStringLiteral("name"))) {
            val = obj.value(QStringLiteral("name"));
            //tempObject = val.toObject();
            //tempString = tempObject.value(QStringLiteral("name"));
            wc_name = val.toString();
        }
        if (obj.contains(QStringLiteral("sys"))) {
            val = obj.value(QStringLiteral("sys"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("country"));
            wc_sys_country = tempString.toString();
        }
        if (obj.contains(QStringLiteral("sys"))) {
            val = obj.value(QStringLiteral("sys"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("id"));
            wc_sys_id = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("sys"))) {
            val = obj.value(QStringLiteral("sys"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("sunrise"));
            wc_sys_sunrise = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("sys"))) {
            val = obj.value(QStringLiteral("sys"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("sunset"));
            wc_sys_sunset = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("sys"))) {
            val = obj.value(QStringLiteral("sys"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("type"));
            wc_sys_type = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("timezone"))) {
            val = obj.value(QStringLiteral("timezone"));
            wc_timezone = val.toDouble();
        }
        if (obj.contains(QStringLiteral("visibility"))) {
            val = obj.value(QStringLiteral("visibility"));
            wc_visibility = val.toDouble();
        }
        if (obj.contains(QStringLiteral("weather"))) {
            val = obj.value(QStringLiteral("weather"));
            tempArray = val.toArray();
            val = tempArray.at(0);
            tempObject = val.toObject();
            wc_weather_description = tempObject.value(QStringLiteral("description")).toString();
            wc_weather_icon = tempObject.value(QStringLiteral("icon")).toString();
            wc_weather_id = tempObject.value(QStringLiteral("id")).toDouble();
            wc_weather_main = tempObject.value(QStringLiteral("main")).toString();
        }

        if (obj.contains(QStringLiteral("wind"))) {
            val = obj.value(QStringLiteral("wind"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("deg"));
            wc_wind_deg = tempString.toDouble();
        }
        if (obj.contains(QStringLiteral("wind"))) {
            val = obj.value(QStringLiteral("wind"));
            tempObject = val.toObject();
            tempString = tempObject.value(QStringLiteral("speed"));
            wc_wind_speed = tempString.toDouble();
        }
    }
}

void weather::loadForecastWeather(){
    qInfo() << "5 Day Forecast";
    QJsonDocument document = QJsonDocument::fromJson(downloadedData());
    qInfo() << "5 Day Forecast was downloaded";
    //qInfo() << document;

    if (document.isObject()) {
        QJsonObject root = document.object();
        QJsonObject jo;
        QJsonArray jv;
        QJsonArray tempArray;
        QJsonValue jj;
        QJsonObject tempObject;
        QJsonValue tempString;
        jj = root.value(QStringLiteral("daily"));
        jv = jj.toArray();
        for(int i =0;i<8;i++){
            jj = jv.at(i);
            jo = jj.toObject();
            if (jo.contains(QStringLiteral("temp"))) {
                jj = jo.value(QStringLiteral("temp"));
                tempObject = jj.toObject();
                tempString = tempObject.value(QStringLiteral("day"));
                 wf_temp_day[i] = niceTemperatureString(tempString.toDouble());
                 tempString = tempObject.value(QStringLiteral("eve"));
                 wf_temp_eve[i] = niceTemperatureString(tempString.toDouble());
                 tempString = tempObject.value(QStringLiteral("max"));
                 wf_temp_max[i] = niceTemperatureString(tempString.toDouble());
                 tempString = tempObject.value(QStringLiteral("min"));
                 wf_temp_min[i] = niceTemperatureString(tempString.toDouble());
                 tempString = tempObject.value(QStringLiteral("morn"));
                 wf_temp_morn[i] = niceTemperatureString(tempString.toDouble());
                 tempString = tempObject.value(QStringLiteral("night"));
                 wf_temp_night[i] = niceTemperatureString(tempString.toDouble());
            }
            if (jo.contains(QStringLiteral("dt"))) {
                jj = jo.value(QStringLiteral("dt"));
                wf_dt[i]= jj.toDouble();
                QDateTime timestamp;
                timestamp.setTime_t(wf_dt[i]);
                wf_day[i]=timestamp.toString("ddd");

            }
            if (jo.contains(QStringLiteral("weather"))) {
                jj = jo.value(QStringLiteral("weather"));
                tempArray = jj.toArray();
                jj = tempArray.at(0);
                tempObject = jj.toObject();
                wf_weather_description[i] = tempObject.value(QStringLiteral("description")).toString();
                wf_weather_icon[i] = tempObject.value(QStringLiteral("icon")).toString();
                wf_weather_id[i] = tempObject.value(QStringLiteral("id")).toDouble();
                wf_weather_main[i] = tempObject.value(QStringLiteral("main")).toString();
            }
        }

        jj = root.value(QStringLiteral("hourly"));
        jv = jj.toArray();
        for(int i =0;i<12;i++){
            jj = jv.at(i);
            jo = jj.toObject();
            if (jo.contains(QStringLiteral("temp"))) {
                tempString = jo.value(QStringLiteral("temp"));
                wfh_temp[i] = tempString.toDouble();
                qInfo() << "tempString: " << tempString;
                qInfo() << "Temp at T+" << i << ": " << wfh_temp[i];
            }
            if (jo.contains(QStringLiteral("pressure"))) {
                qInfo() << "It does contain Pressure";
                tempString = jo.value(QStringLiteral("pressure"));

                wfh_pressure[i] = tempString.toDouble();
                qInfo() << "Pressure at T+" << i << ": " << wfh_pressure[i];
            }
            if (jo.contains(QStringLiteral("humidity"))) {
                tempString = jo.value(QStringLiteral("humidity"));
                wfh_humidity[i] = tempString.toDouble();
                qInfo() << "Humidity at T+" << i << ": " << wfh_humidity[i];
            }
            if (jo.contains(QStringLiteral("dt"))) {
                jj = jo.value(QStringLiteral("dt"));
                wfh_dt[i]= jj.toDouble();
                QDateTime timestamp;
                timestamp.setTime_t(wfh_dt[i]);
                wfh_day[i]=timestamp.toString("hh mm");
                qInfo() << "Hour at T+" << i << ": " << wfh_day[i];
            }
            if (jo.contains(QStringLiteral("weather"))) {
                jj = jo.value(QStringLiteral("weather"));
                tempArray = jj.toArray();
                jj = tempArray.at(0);
                tempObject = jj.toObject();
                wfh_weather_description[i] = tempObject.value(QStringLiteral("description")).toString();
                qInfo() << "Description at T+" << i << ": " << wfh_weather_description[i];
                wfh_weather_icon[i] = tempObject.value(QStringLiteral("icon")).toString();
                qInfo() << "Icon at T+" << i << ": " << wfh_weather_icon[i];
                wfh_weather_id[i] = tempObject.value(QStringLiteral("id")).toDouble();
                qInfo() << "Id  at T+" << i << ": " << wfh_weather_id[i];
                wfh_weather_main[i] = tempObject.value(QStringLiteral("main")).toString();
                qInfo() << "Main at T+" << i << ": " << wfh_weather_main[i];
            }
        }

    }
}

double weather::gettemp1()
{
    return wfh_temp[0];
}

double weather::gettemp2()
{
    return wfh_temp[1];
}

double weather::gettemp3()
{
    return wfh_temp[2];
}

double weather::gettemp4()
{
    return wfh_temp[3];
}

double weather::gettemp5()
{
    return wfh_temp[4];
}
double weather::gettemp6()
{
    return wfh_temp[5];
}

double weather::gettemp7()
{
    return wfh_temp[6];
}

double weather::gettemp8()
{
    return wfh_temp[7];
}

double weather::gettemp9()
{
    return wfh_temp[8];
}

double weather::gettemp10()
{
    return wfh_temp[9];
}

double weather::gettemp11()
{
    return wfh_temp[10];
}

double weather::gettemp12()
{
    return wfh_temp[11];
}
