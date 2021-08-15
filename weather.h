#ifndef WEATHER_H
#define WEATHER_H

#include <QEventLoop>
#include <QTime>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class weather : public QEventLoop
{
    Q_OBJECT
public:
    double gettemp1();
    double gettemp2();
    double gettemp3();
    double gettemp4();
    double gettemp5();
    double gettemp6();
    double gettemp7();
    double gettemp8();
    double gettemp9();
    double gettemp10();
    double gettemp11();
    double gettemp12();
   explicit weather(QObject *parent = nullptr);
   virtual ~weather();
   QTimer *wc_timer;
   QTimer *wf_timer;
   QByteArray downloadedData() const;

   //Current Weather Data
   QString wc_base;
   double wc_clouds_all;
   double wc_cod;
   double wc_coord_lat;
   double wc_coord_lon;
   double wc_dt; //time of data calculation
   double wc_id; //city id
   QString wc_main_feels_like;
   double wc_main_humidity;
   double wc_main_pressure;
   QString wc_main_temp;
   QString wc_main_temp_max;
   QString wc_main_temp_min;
   QString wc_name; //City Name
   QString wc_sys_country;
   double wc_sys_id; // internal parameter
   double wc_sys_sunrise;
   double wc_sys_sunset;
   double wc_sys_type; // internal parameter
   double wc_timezone; // need for unix timsestamp calculation
   double wc_visibility; //in meter
   QString wc_weather_description;
   QString wc_weather_icon;
   double wc_weather_id;
   QString wc_weather_main;
   double wc_wind_deg;
   double wc_wind_speed;
   //Forecast Weather Data
   QString wf_temp_day[8];
   QString wf_temp_eve[8];
   QString wf_temp_max[8];
   QString wf_temp_min[8];
   QString wf_temp_morn[8];
   QString wf_temp_night[8];
   double wf_dt[8];
   QString wf_day[8];
   QString wf_weather_description[8];
   QString wf_weather_icon[8];
   double wf_weather_id[8];
   QString wf_weather_main[8];
    void init();
   double wfh_temp[12];
   double wfh_pressure[12];
   double wfh_humidity[12];
   double wfh_dt[12];
   QString wfh_day[12];
   QString wfh_weather_description[12];
   QString wfh_weather_icon[12];
   double wfh_weather_id[12];
   QString wfh_weather_main[12];

public slots:
   void refreshCurrentWeather();
   void refreshForecastWeather();
   void loadCurrentWeather();
   void loadForecastWeather();
private:
   QNetworkAccessManager m_WebCtrl;
   QNetworkAccessManager m_forecase_WebCtrl;
   QByteArray m_DownloadedData;

    QJsonObject jsonObj;
    QJsonObject weather_obj;
    QString AppId;
    QString City;
    QString lat;
    QString lon;
private slots:
     void fileDownloaded(QNetworkReply* pReply);
     void forecastfileDownloaded(QNetworkReply* pReply);


signals:
      void downloaded();
      void forecastdownloaded();
};

#endif // WEATHER_H
