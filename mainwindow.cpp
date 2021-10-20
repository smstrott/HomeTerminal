#include "mainwindow.h"
#include "forecastwindow.h"
#include "navigationwindow.h"
#include <qicon.h>
#include <qsize.h>


#define ZERO_KELVIN 273.15

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MainWindow::setStyleSheet("background-color:darkblue;");
    MainWindow::setStyleSheet("color: black; background-color: silver");
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    QTimer *systimer = new QTimer(this);
    systimer->start(60000);
    counter = 0;
    lbl_clk = new QLabel("time", this);
    lbl_clk->setGeometry(370, 10, 150, 30);
    QFont fnt_clk( "Verdana", 24, QFont::Bold);
    lbl_clk->setFont(fnt_clk);
    setWeatherShow();
    setForecastWatherShow();
    SetshowTraffic();
    SetshowSysInfo();
    bnthm = new QPushButton(this);
    bnthm->setGeometry(0, 0, 50, 50);
    icon.addFile(":/button_icons/Menu.svg");
    bnthm->setIcon(icon);
    bnthm->setIconSize(QSize(50,50));
    mtraffic = new traffic(this);
    mtraffic->init();
    mtraffic->refreshTraffic();
    mweather = new weather(this);
    mweather->init();
    mweather->refreshCurrentWeather();
    mweather->refreshForecastWeather();
    MainWindow::showCurrentWather();
    MainWindow::showTraffic();
    MainWindow::showSysInfo();
    qInfo() << "before NavigarionWindow";
    nav_win = new NavigationWindow();
    qInfo() << "after NavigationWindow";
    nav_win->setGeometry(0, 50, 100, 200);
    nav_win->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::showCurrentWather);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::showTraffic);
    QObject::connect(systimer, &QTimer::timeout, this, &MainWindow::showSysInfo);
    QObject::connect(bnthm, SIGNAL(clicked()), this, SLOT(button_hmClicked()));
}

MainWindow::~MainWindow() {
}


void MainWindow::detailedWeather(){
    //gView = new QGraphicsView(this);
    //scene = new QGraphicsScene;
    QGraphicsView gView;
    QGraphicsScene scene;
    QSvgWidget svgWid;
    svgWid.setGeometry(0, 150, 30, 30);
    //svgWid.setAttribute(Qt::WA_TranslucentBackground, true);
    //svgWid.setContentsMargins(0, 0, 0, 0);
    svgWid.setAutoFillBackground(true);
    scene.addWidget(&svgWid);
    gView.resize(480, 270);
    gView.setScene(&scene);


}
void MainWindow::getCPUTemp()
{
    QProcess *myProcess = new QProcess();
    QString program = "/opt/vc/bin/vcgencmd";
    QStringList arguments;
    arguments << "measure_temp";
    myProcess->start(program, arguments);
    myProcess->waitForFinished(1000);
    QString result = myProcess->readAllStandardOutput();
    Sys_CPU_temp = result.mid(5,2);
    Sys_CPU_temp.append("°C");
    qInfo() << Sys_CPU_temp;
}

void MainWindow::getFreeRAM()
{
    QProcess *myProcess = new QProcess();
    QString program = "free";
    QStringList arguments;
    arguments << "-h";
    myProcess->start(program, arguments);
    myProcess->waitForFinished(1000);
    QString result = myProcess->readAllStandardOutput();
    QStringList list1 = result.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QString UsedMem = list1.at(12);
    double MemUsed = UsedMem.mid(0, UsedMem.length()-2).toDouble();
    qInfo() << "Used Memory: " << MemUsed;
    QString TotalMem = list1.at(7);
    double MemTotal = TotalMem.mid(0, TotalMem.length()-2).toDouble();
    qInfo() << "Total Memory: " << MemTotal;
    Sys_Mem = (MemUsed/MemTotal)*100;
    qInfo() << "Momory Usage: " << QString::number(Sys_Mem) << "%";
}

void MainWindow::getCPULoad()
{
    QProcess *myProcess = new QProcess();
    QString program = "w";
    QStringList arguments;
    arguments << "-s";
    myProcess->start(program, arguments);
    myProcess->waitForFinished(1000);
    QString result = myProcess->readAllStandardOutput();
    QStringList list1 = result.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QString CPULoadAvg1 = list1.at(7);
    QString Avg1CPULod = CPULoadAvg1.replace(1,1,".");
    QString Avg1CPULod2 = Avg1CPULod.mid(0, Avg1CPULod.length()-1);
    Sys_CPU_1 = Avg1CPULod2.toDouble()*100;
    qInfo() << "1 Minute avg CPU Load: " << QString::number(Sys_CPU_1) << "%";
    QString CPULoadAvg2 = list1.at(8);
    QString Avg2CPULod = CPULoadAvg2.replace(1,1,".");
    QString Avg2CPULod2 = Avg2CPULod.mid(0, Avg1CPULod.length()-1);
    Sys_CPU_5 = Avg2CPULod2.toDouble()*100;
    qInfo() << "5 Minute avg CPU Load: " << QString::number(Sys_CPU_5) << "%";
    QString CPULoadAvg3 = list1.at(9);
    QString Avg3CPULod = CPULoadAvg3.replace(1,1,".");
    QString Avg3CPULod2 = Avg3CPULod.mid(0, Avg1CPULod.length()-1);
    Sys_CPU_15 = Avg3CPULod2.toDouble()*100;
    qInfo() << "15 Minute avg CPU Load: " << QString::number(Sys_CPU_15) << "%";
}

void MainWindow::SetshowSysInfo()
{
    //lbl_Sys_CPU_1 = new QLabel("BVG 1", this);
    //lbl_Sys_CPU_1->setGeometry(0, 268, 150, 16);
    //lbl_Sys_CPU_1->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    //lbl_Sys_CPU_5 = new QLabel("BVG 1", this);
    //lbl_Sys_CPU_5->setGeometry(0, 284, 150, 16);
    //lbl_Sys_CPU_5->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    lbl_Sys_CPU_15 = new QLabel("BVG 1", this);
    lbl_Sys_CPU_15->setGeometry(0, 300, 150, 16);
    lbl_Sys_CPU_15->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    lbl_Sys_CPU_temp = new QLabel("BVG 1", this);
    lbl_Sys_CPU_temp->setGeometry(200, 295, 96, 25);
    lbl_Sys_CPU_temp->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    lbl_Sys_Mem = new QLabel("BVG 1", this);
    lbl_Sys_Mem->setGeometry(384, 295, 96, 25);
    lbl_Sys_Mem->setStyleSheet("QLabel { background-color : yellow; color : black; }");
}
void MainWindow::SetshowTraffic()
{

    BVG_Head = new QLabel("Weil wir dich Lieben", this);
    BVG_Head->setGeometry(220, 5, 150, 40);
    BVG_Head->setStyleSheet("QLabel {color : black; }");
    QFont fnt_traffic( "Verdana", 11);
    BVG_Head->setFont(fnt_traffic);
    //QString logopath = ":/bvg_small.svg";
    //BVG_logo->load(logopath);
    BVG_logo = new QSvgWidget(":/bvg_small.svg", this);
    BVG_logo->setGeometry(180, 5, 40, 40);


    BVG_1 = new QLabel("BVG 1", this);
    BVG_1->setGeometry(180, 50, 275, 25);
    BVG_1->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_1->setFont(fnt_traffic);
    BVG_1_dep = new QLabel("BVG 1", this);
    BVG_1_dep->setGeometry(455, 50, 25, 25);
    BVG_1_dep->setFont(fnt_traffic);


    BVG_2 = new QLabel("BVG 2", this);
    BVG_2->setGeometry(180, 75, 275, 25);
    BVG_2->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_2->setFont(fnt_traffic);
    BVG_2_dep = new QLabel("BVG 1", this);
    BVG_2_dep->setGeometry(455, 75, 25, 25);
    BVG_2_dep->setFont(fnt_traffic);


    BVG_3 = new QLabel("BVG ", this);
    BVG_3->setGeometry(180, 100, 275, 25);
    BVG_3->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_3->setFont(fnt_traffic);
    BVG_3_dep = new QLabel("BVG 1", this);
    BVG_3_dep->setGeometry(455, 100, 25, 25);
    BVG_3_dep->setFont(fnt_traffic);


    BVG_4 = new QLabel("BVG 4", this);
    BVG_4->setGeometry(180, 125, 275, 25);
    BVG_4->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_4->setFont(fnt_traffic);
    BVG_4_dep = new QLabel("BVG 1", this);
    BVG_4_dep->setGeometry(455, 125, 25, 25);
    BVG_4_dep->setFont(fnt_traffic);


    BVG_5 = new QLabel("BVG 5", this);
    BVG_5->setGeometry(180, 150, 275, 25);
    BVG_5->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_5->setFont(fnt_traffic);
    BVG_5_dep = new QLabel("BVG 1", this);
    BVG_5_dep->setGeometry(455, 150, 25, 25);
    BVG_5_dep->setFont(fnt_traffic);


    BVG_6 = new QLabel("BVG 6", this);
    BVG_6->setGeometry(180, 175, 275, 25);
    BVG_6->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_6->setFont(fnt_traffic);
    BVG_6_dep = new QLabel("BVG 1", this);
    BVG_6_dep->setGeometry(455, 175, 25, 25);
    BVG_6_dep->setFont(fnt_traffic);


    BVG_7 = new QLabel("BVG 6", this);
    BVG_7->setGeometry(180, 200, 275, 25);
    BVG_7->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_7->setFont(fnt_traffic);
    BVG_7_dep = new QLabel("BVG 1", this);
    BVG_7_dep->setGeometry(455, 200, 25, 25);
    BVG_7_dep->setFont(fnt_traffic);


    BVG_8 = new QLabel("BVG 6", this);
    BVG_8->setGeometry(180, 225, 275, 25);
    BVG_8->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_8->setFont(fnt_traffic);
    BVG_8_dep = new QLabel("BVG 1", this);
    BVG_8_dep->setGeometry(455, 225, 25, 25);
    BVG_8_dep->setFont(fnt_traffic);


    BVG_9 = new QLabel("BVG 6", this);
    BVG_9->setGeometry(180, 250, 275, 25);
    BVG_9->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    BVG_9->setFont(fnt_traffic);
    BVG_9_dep = new QLabel("BVG 1", this);
    BVG_9_dep->setGeometry(455, 250, 25, 25);
    BVG_9_dep->setFont(fnt_traffic);

}

void MainWindow::showSysInfo()
{
    MainWindow::getCPUTemp();
    MainWindow::getFreeRAM();
    MainWindow::getCPULoad();

    //lbl_Sys_CPU_1->setStyleSheet("QLabel { background-color : silver ; color : black; }");
    //lbl_Sys_CPU_1->setText("1 min CPU Load avg: " + QString::number(Sys_CPU_1));
    //lbl_Sys_CPU_5->setStyleSheet("QLabel { background-color : silver ; color : black; }");
    //lbl_Sys_CPU_5->setText("5 min CPU Load avg: " + QString::number(Sys_CPU_5));
    lbl_Sys_CPU_15->setStyleSheet("QLabel { background-color : silver ; color : black; }");
    lbl_Sys_CPU_15->setText("15 min CPU Load avg: " + QString::number(Sys_CPU_15));

    lbl_Sys_CPU_temp->setStyleSheet("QLabel { background-color : silver ; color : black; }");
    lbl_Sys_CPU_temp->setText("CPU Temp.: " + Sys_CPU_temp + "C");

    lbl_Sys_Mem->setStyleSheet("QLabel { background-color : silver ; color : black; }");
    lbl_Sys_Mem->setText("Mem usg.: " + QString::number(Sys_Mem) + "%");
    qInfo() << "showSysInfo done";
}


void MainWindow::showTraffic()
{
    BVG_1->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[0] + "; color : black; }");
    BVG_1->setText(mtraffic->BVG_name[0] + ": " + mtraffic->BVG_direction[0]);
    BVG_1_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[0] + "; color : black; }");
    BVG_1_dep->setText(mtraffic->BVG_minutesTo[0] + "'");

    BVG_2->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[1] + "; color : black; }");
    BVG_2->setText(mtraffic->BVG_name[1] + ": " + mtraffic->BVG_direction[1]);
    BVG_2_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[1] + "; color : black; }");
    BVG_2_dep->setText(mtraffic->BVG_minutesTo[1] + "'");
    BVG_3->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[2] + "; color : black; }");
    BVG_3->setText(mtraffic->BVG_name[2] + ": " + mtraffic->BVG_direction[2]);
    BVG_3_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[2] + "; color : black; }");
    BVG_3_dep->setText(mtraffic->BVG_minutesTo[2] + "'");
    BVG_4->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[3] + "; color : black; }");
    BVG_4->setText(mtraffic->BVG_name[3] + ": " + mtraffic->BVG_direction[3]);
    BVG_4_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[3] + "; color : black; }");
    BVG_4_dep->setText(mtraffic->BVG_minutesTo[3] + "'");
    BVG_5->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[4] + "; color : black; }");
    BVG_5->setText(mtraffic->BVG_name[4] + ": " + mtraffic->BVG_direction[4]);
    BVG_5_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[4] + "; color : black; }");
    BVG_5_dep->setText(mtraffic->BVG_minutesTo[4] + "'");
    BVG_6->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[5] + "; color : black; }");
    BVG_6->setText(mtraffic->BVG_name[5] + ": " + mtraffic->BVG_direction[5]);
    BVG_6_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[5] + "; color : black; }");
    BVG_6_dep->setText(mtraffic->BVG_minutesTo[5] + "'");
    BVG_7->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[6] + "; color : black; }");
    BVG_7->setText(mtraffic->BVG_name[6] + ": " + mtraffic->BVG_direction[6]);
    BVG_7_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[6] + "; color : black; }");
    BVG_7_dep->setText(mtraffic->BVG_minutesTo[6] + "'");
    BVG_8->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[7] + "; color : black; }");
    BVG_8->setText(mtraffic->BVG_name[7] + ": " + mtraffic->BVG_direction[7]);
    BVG_8_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[7] + "; color : black; }");
    BVG_8_dep->setText(mtraffic->BVG_minutesTo[7] + "'");
    BVG_9->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[8] + "; color : black; }");
    BVG_9->setText(mtraffic->BVG_name[8] + ": " + mtraffic->BVG_direction[8]);
    BVG_9_dep->setStyleSheet("QLabel { background-color : " + mtraffic->bgColor_hex[8] + "; color : black; }");
    BVG_9_dep->setText(mtraffic->BVG_minutesTo[8] + "'");
}

void MainWindow::setForecastWatherShow()
{
    //Global Size Variables
    int temp_height = 24;
    int temp_width = 150;
    int min_height = 12;
    int max_height = 12;
    int min_width = 75;
    int max_width = 75;
    int temp_x_pos = 200;
    int x_pos_day = 2;
    int x_pos_L = 70;
    int x_pos = 5;

    // Day Plus 1
    lbl_wf1_day = new QLabel("wf_day", this);
    lbl_wf1_day->setGeometry(x_pos_day, 85, temp_width, temp_height);
    lbl_wf1_min = new QLabel("wf_min", this);
    lbl_wf1_min->setGeometry(x_pos_L, 98, min_width, min_height);
    lbl_wf1_min->setStyleSheet(minColor);
    lbl_wf1_max = new QLabel("wf_max", this);
    lbl_wf1_max->setGeometry(x_pos_L, 84, max_width, max_height);
    lbl_wf1_max->setStyleSheet(maxColor);
    icn_wf1 = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wf1->setGeometry(130, 75, 40, 40);
    // Day Plus 2
    lbl_wf2_day = new QLabel("wf_day", this);
    lbl_wf2_day->setGeometry(x_pos_day, 125, temp_width, temp_height);
    lbl_wf2_min = new QLabel("wf_min", this);
    lbl_wf2_min->setGeometry(x_pos_L, 138, min_width, min_height);
    lbl_wf2_min->setStyleSheet(minColor);
    lbl_wf2_max = new QLabel("wf_max", this);
    lbl_wf2_max->setGeometry(x_pos_L, 124, max_width, max_height);
    lbl_wf2_max->setStyleSheet(maxColor);
    icn_wf2 = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wf2->setGeometry(130, 115, 40, 40);
    // Day Plus 3
    lbl_wf3_day = new QLabel("wf_temp", this);
    lbl_wf3_day->setGeometry(x_pos_day, 165, temp_width, temp_height);
    lbl_wf3_min = new QLabel("wf_min", this);
    lbl_wf3_min->setGeometry(x_pos_L, 178, min_width, min_height);
    lbl_wf3_min->setStyleSheet(minColor);
    lbl_wf3_max = new QLabel("wf_max", this);
    lbl_wf3_max->setGeometry(x_pos_L, 164, max_width, max_height);
    lbl_wf3_max->setStyleSheet(maxColor);
    icn_wf3 = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wf3->setGeometry(130, 155, 40, 40);
    // Day Plus 4
    lbl_wf4_day = new QLabel("wf_temp", this);
    lbl_wf4_day->setGeometry(x_pos_day, 205, temp_width, temp_height);
    lbl_wf4_min = new QLabel("wf_min", this);
    lbl_wf4_min->setGeometry(x_pos_L, 218, min_width, min_height);
    lbl_wf4_min->setStyleSheet(minColor);
    lbl_wf4_max = new QLabel("wf_max", this);
    lbl_wf4_max->setGeometry(x_pos_L, 204, max_width, max_height);
    lbl_wf4_max->setStyleSheet(maxColor);
    icn_wf4 = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wf4->setGeometry(130, 195, 40, 40);
    // Day Plus 4
    lbl_wf5_day = new QLabel("wf_temp", this);
    lbl_wf5_day->setGeometry(x_pos_day, 245, temp_width, temp_height);
    lbl_wf5_min = new QLabel("wf_min", this);
    lbl_wf5_min->setGeometry(x_pos_L, 258, min_width, min_height);
    lbl_wf5_min->setStyleSheet(minColor);
    lbl_wf5_max = new QLabel("wf_max", this);
    lbl_wf5_max->setGeometry(x_pos_L, 244, max_width, max_height);
    lbl_wf5_max->setStyleSheet(maxColor);
    icn_wf5 = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wf5->setGeometry(130, 235, 40, 40);

    QFont fnt_wf_temp( "Verdana", 24, QFont::Bold);
    lbl_wf1_day->setFont(fnt_wf_temp);
    lbl_wf2_day->setFont(fnt_wf_temp);
    lbl_wf3_day->setFont(fnt_wf_temp);
    lbl_wf4_day->setFont(fnt_wf_temp);
    lbl_wf5_day->setFont(fnt_wf_temp);

    QFont fnt_wf_min( "Verdana", 12, QFont::Bold);
    lbl_wf1_min->setFont(fnt_wf_min);
    lbl_wf2_min->setFont(fnt_wf_min);
    lbl_wf3_min->setFont(fnt_wf_min);
    lbl_wf4_min->setFont(fnt_wf_min);
    lbl_wf5_min->setFont(fnt_wf_min);

    QFont fnt_wf_max( "Verdana", 12, QFont::Bold);
    lbl_wf1_max->setFont(fnt_wf_max);
    lbl_wf2_max->setFont(fnt_wf_max);
    lbl_wf3_max->setFont(fnt_wf_max);
    lbl_wf4_max->setFont(fnt_wf_max);
    lbl_wf5_max->setFont(fnt_wf_max);
}

void MainWindow::setWeatherShow(){
    //Global Size Variables
    int temp_height = 40;
    int temp_width = 150;
    int min_height = 25;
    int max_height = 25;
    // Current Lables
    lbl_wc_temp = new QLabel("wc_temp", this);
    lbl_wc_temp->setGeometry(60, 10, temp_width, temp_height);
    icn_wc = new QSvgWidget(":/weather_icons/wi-alien.svg", this);
    icn_wc->setGeometry(120, 0, 60, 60);

    lbl_wc_min = new QLabel("wc_min", this);
    lbl_wc_min->setGeometry(2, 50, 150, min_height);
    lbl_wc_min->setStyleSheet(minColor);
    lbl_wc_max = new QLabel("wc_max", this);
    lbl_wc_max->setGeometry(70, 50, 150, max_height);
    lbl_wc_max->setStyleSheet(maxColor);

    QFont fnt_wc_temp_main( "Verdana", 32, QFont::Bold);

    lbl_wc_temp->setFont(fnt_wc_temp_main);

    QFont fnt_wc_min_main( "Verdana", 16, QFont::Bold);
    lbl_wc_min->setFont(fnt_wc_min_main);

    QFont fnt_wc_max_main( "Verdana", 16, QFont::Bold);
    lbl_wc_max->setFont(fnt_wc_max_main);


}


void MainWindow::showCurrentWather(){
    lbl_wc_temp->setText(mweather->wc_main_temp);
    lbl_wc_max->setText("H: " + mweather->wf_temp_max[0]);
    lbl_wc_min->setText("L: " + mweather->wf_temp_min[0]);
    lbl_wf1_day->setText(mweather->wf_day[1]);
    lbl_wf1_max->setText("H: " + mweather->wf_temp_max[1]);
    lbl_wf1_min->setText("L: " + mweather->wf_temp_min[1]);
    icn_wf1->load(MainWindow::setWeatherIcon(mweather->wf_weather_icon[1]));
    lbl_wf2_day->setText(mweather->wf_day[2]);
    lbl_wf2_max->setText("H: " + mweather->wf_temp_max[2]);
    lbl_wf2_min->setText("L: " + mweather->wf_temp_min[2]);
    icn_wf2->load(MainWindow::setWeatherIcon(mweather->wf_weather_icon[2]));
    lbl_wf3_day->setText(mweather->wf_day[3]);
    lbl_wf3_max->setText("H: " + mweather->wf_temp_max[3]);
    lbl_wf3_min->setText("L: " + mweather->wf_temp_min[3]);
    icn_wf3->load(MainWindow::setWeatherIcon(mweather->wf_weather_icon[3]));
    lbl_wf4_day->setText(mweather->wf_day[4]);
    lbl_wf4_max->setText("H: " + mweather->wf_temp_max[4]);
    lbl_wf4_min->setText("L: " + mweather->wf_temp_min[4]);
    icn_wf4->load(MainWindow::setWeatherIcon(mweather->wf_weather_icon[4]));
    lbl_wf5_day->setText(mweather->wf_day[5]);
    lbl_wf5_max->setText("H: " + mweather->wf_temp_max[5]);
    lbl_wf5_min->setText("L: " + mweather->wf_temp_min[5]);
    icn_wf5->load(MainWindow::setWeatherIcon(mweather->wf_weather_icon[5]));
    QString filename =":/weather_icons/wi-na.svg";
    QString word = "bla";
    icn_wc->load(MainWindow::setWeatherIcon(mweather->wc_weather_icon));
}

QString MainWindow::setWeatherIcon(QString iconId)
{
    QString filename;
    if(iconId == "01d"){
        filename=":/weather_icons/wi-day-sunny.svg";
    }else if(iconId==  "01n"){
        filename=":/weather_icons/wi-night-clear.svg";
    }else if(iconId ==  "02d"){
        filename=":/weather_icons/wi-day-cloudy.svg";
    }else if(iconId ==  "02n"){
        filename=":/weather_icons/wi-night-cloudy.svg";
    }else if(iconId ==  "03d"){
        filename=":/weather_icons/wi-day-cloudy.svg";
    }else if(iconId ==  "03n"){
        filename=":/weather_icons/wi-night-cloudy.svg";
    }else if(iconId ==  "04d"){
        filename=":/weather_icons/wi-day-cloudy.svg";
    }else if(iconId ==  "04n"){
        filename=":/weather_icons/wi-night-cloudy.svg";
    }else if(iconId==  "09d"){
        filename=":/weather_icons/wi-rain.svg";
    }else if(iconId==  "09n"){
        filename=":/weather_icons/wi-rain.svg";
    }else if(iconId ==  "10d"){
        filename=":/weather_icons/wi-day-rain.svg";
    }else if(iconId ==  "10n"){
        filename=":/weather_icons/wi-night-rain.svg";
    }else if(iconId ==  "11d"){
        filename=":/weather_icons/wi-thunderstorm.svg";
    }else if(iconId ==  "11n"){
        filename=":/weather_icons/wi-thunderstorm.svg";
    } else if(iconId==  "13d"){
        filename=":/weather_icons/wi-day-snow.svg";
    } else if(iconId ==  "13n"){
        filename=":/weather_icons/wi-night-snow.svg";
    }else if(iconId ==  "50d"){
        filename=":/weather_icons/wi-day-fog.svg";
    }else if(iconId ==  "50n"){
        filename=":/weather_icons/wi-night-fog.svg";
    }else {
        filename =":/weather_icons/wi-na.svg";
    }
    return filename;
}

void MainWindow::button_hmClicked()
{

   nav_win->showFullScreen();
}

void MainWindow::showTime()

{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    lbl_clk->setText(text);
}

void MainWindow::createMenus() {
  QMenuBar *bar = menuBar();
  QMenu *fileMenu = bar->addMenu(tr("&File"));
  fileMenu->addAction(new QAction("Open", this));
  fileMenu->addAction(new QAction("Close", this));
}



