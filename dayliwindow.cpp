#include "dayliwindow.h"


QT_CHARTS_USE_NAMESPACE

DayliWindow::DayliWindow(QWidget *parent)
    : QMainWindow(parent)
{
    bnthm = new QPushButton(this);
    bnthm->setGeometry(0, 0, 50, 50);
    icon.addFile(":/button_icons/return.svg");
    bnthm->setIcon(icon);
    bnthm->setIconSize(QSize(50,50));
    //DayliWindow::setGraphicalElements();
    QObject::connect(bnthm, SIGNAL(clicked()), this, SLOT(bnt_d_hide()));
}

void DayliWindow::bnt_d_hide()
{
    DayliWindow::setGraphicalElements ();
    this->hide();
}

DayliWindow::~DayliWindow() {
}


void DayliWindow::setGraphicalElements ()
{
    QFont timefont( "Verdana", 12, QFont::Bold);
    QSplineSeries *series = new QSplineSeries();
    mmweather = new weather(this);
    series->setName("spline");
    qInfo() << "gettemp1: " << mmweather->gettemp1();
    qInfo() << "gettemp2: " << mmweather->gettemp2();
    qInfo() << "gettemp3: " << mmweather->gettemp3();
    qInfo() << "gettemp4: " << mmweather->gettemp4();
    qInfo() << "gettemp5: " << mmweather->gettemp5();
    qInfo() << "gettemp6: " << mmweather->gettemp6();
    qInfo() << "gettemp7: " << mmweather->gettemp7();
    qInfo() << "gettemp8: " << mmweather->gettemp8();
    qInfo() << "gettemp9: " << mmweather->gettemp9();
    qInfo() << "gettemp10: " << mmweather->gettemp10();
    qInfo() << "gettemp11: " << mmweather->gettemp11();
    qInfo() << "gettemp12: " << mmweather->gettemp12();
    series->append(1, mmweather->gettemp1());
    series->append(2, mmweather->gettemp2());
    series->append(3, mmweather->gettemp3());
    series->append(4, mmweather->gettemp4());
    series->append(5, mmweather->gettemp5());
    series->append(6, mmweather->gettemp6());
    series->append(7, mmweather->gettemp7());
    series->append(8, mmweather->gettemp8());
    series->append(9, mmweather->gettemp9());
    series->append(10, mmweather->gettemp10());
    series->append(11, mmweather->gettemp11());
    series->append(12, mmweather->gettemp12());

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    int min = 1;
    int max = 12;
    chart->axes(Qt::Vertical).first()->setRange(min, max);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // create central widget and layout
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    setCentralWidget(mainWidget);


    // create a splitter and two colorfull dummies
    QSplitter *splitter = new QSplitter(this);

    QWidget *dummy1 = new QWidget(this);
    dummy1->setStyleSheet("background-color: rgb(255, 100, 100)");
    bnthm = new QPushButton(dummy1);
    bnthm->setGeometry(0, 0, 50, 50);
    icon.addFile(":/button_icons/return.svg");
    bnthm->setIcon(icon);
    bnthm->setIconSize(QSize(50,50));

    timePlus1 = new QLabel("T+1", dummy1);
    timePlus1->setGeometry(50,0,50,50);
    timePlus1->setText("22:00");
    timePlus1->setFont(timefont);
    iconPlus1 = new QSvgWidget(":/weather_icons/wi-alien.svg", dummy1);
    iconPlus1->setGeometry(50, 30, 50, 50);

    // create a chart in a chartview
    //chart->setMinimumSize(100, 100);

    // add all to splitter
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(dummy1);
    splitter->addWidget(chartView);

    // remove contentMargins
    chart       -> setContentsMargins(0,0,0,0);
    chartView   -> setContentsMargins(0,0,0,0);
    splitter    -> setContentsMargins(0,0,0,0);
    mainLayout  -> setContentsMargins(0,0,0,0);

    // output
    mainLayout->addWidget(splitter);



}
