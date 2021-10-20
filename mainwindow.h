#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QPushButton>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgWidget>
#include <QStackedWidget>
#include <QPixmap>
#include <QListView>
#include <QTcpSocket>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QProcess>

#include "traffic.h"
#include "weather.h"
#include "ui_mainwindow.h"
#include "forecastwindow.h"
#include "navigationwindow.h"

//#include "digitalclock.h"


//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    int counter;
    QLabel* label;
    QLabel* lbl_clk;
    QLabel* lbl_wc_temp;
    QLabel* lbl_wc_min;
    QLabel* lbl_wc_max;
    QSvgWidget *icn_wc;
    QLabel* lbl_wf1_day;
    QLabel* lbl_wf1_min;
    QLabel* lbl_wf1_max;
    QSvgWidget *icn_wf1;
    QLabel* lbl_wf2_day;
    QLabel* lbl_wf2_min;
    QLabel* lbl_wf2_max;
    QSvgWidget *icn_wf2;
    QLabel* lbl_wf3_day;
    QLabel* lbl_wf3_min;
    QLabel* lbl_wf3_max;
    QSvgWidget *icn_wf3;
    QLabel* lbl_wf4_day;
    QLabel* lbl_wf4_min;
    QLabel* lbl_wf4_max;
    QSvgWidget *icn_wf4;
    QLabel* lbl_wf5_day;
    QLabel* lbl_wf5_min;
    QLabel* lbl_wf5_max;
    QSvgWidget *icn_wf5;
    QLabel* lbl_wf6_day;
    QLabel* lbl_wf6_min;
    QLabel* lbl_wf6_max;
    QSvgWidget *icn_wf6;
    QLabel* lbl_wf7_day;
    QLabel* lbl_wf7_min;
    QLabel* lbl_wf7_max;
    QSvgWidget *icn_wf7;
    QLabel* wc_icon;
    QString minColor = "color:rgb(0,76,153);";
    QString maxColor = "color:rgb(200,0,0);";

    QSvgWidget *BVG_logo;
    QLabel* BVG_Head;
    QLabel* BVG_1;
    QLabel* BVG_2;
    QLabel* BVG_3;
    QLabel* BVG_4;
    QLabel* BVG_5;
    QLabel* BVG_6;
    QLabel* BVG_7;
    QLabel* BVG_8;
    QLabel* BVG_9;
    QLabel* BVG_1_dep;
    QLabel* BVG_2_dep;
    QLabel* BVG_3_dep;
    QLabel* BVG_4_dep;
    QLabel* BVG_5_dep;
    QLabel* BVG_6_dep;
    QLabel* BVG_7_dep;
    QLabel* BVG_8_dep;
    QLabel* BVG_9_dep;

    QJsonObject traffic_obj;
    QString accessId;
    QString id;

    //QLabel* lbl_Sys_CPU_1;
    //QLabel* lbl_Sys_CPU_5;
    QLabel* lbl_Sys_CPU_15;
    QLabel* lbl_Sys_CPU_temp;
    QLabel* lbl_Sys_Mem;
    int Sys_CPU_1;
    int Sys_CPU_5;
    int Sys_CPU_15;
    QString Sys_CPU_temp;
    int Sys_Mem;




    QPushButton* bnthm;
    QFont* clkfont;

    virtual ~MainWindow();

    //QByteArray downloadedTraffic() const;


    QGraphicsView *gView;
    QGraphicsScene *scene;

    int windowctrl = 0;
    QProcess myProcess;

public slots:
  void button_hmClicked();
  void showTime();

  //void loadCurrentTraffic();


private:
  QIcon icon;
  NavigationWindow *nav_win;
  //ForecastWindow *fc_win;
  //QByteArray m_downloadedTraffic;
  QSvgRenderer *renderer;
  QGraphicsSvgItem *black ;
  QGraphicsSvgItem *red;
  //QGraphicsSvgItem *item;
  QSize p;

  //Stacked widgets
  traffic *mtraffic{nullptr};
  weather *mweather{nullptr};
  QString setWeatherIcon(QString iconId);
  QString getAPPId();

  void init();


private slots:
  void createMenus();

  //void trafficDownloaded(QNetworkReply* pReply);


  void showCurrentWather();
  void showTraffic();
  void SetshowTraffic();
  void SetshowSysInfo();
  void setWeatherShow();
  void setForecastWatherShow();
  void detailedWeather();
  //void refreshTraffic();
  //void setCurrentIcon();
  void getCPUTemp();
  void getFreeRAM();
  void getCPULoad();
  void showSysInfo();



signals:


};



#endif // MAINWINDOW_H
