#ifndef DAYLIWINDOW_H
#define DAYLIWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QSvgWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QGridLayout>
#include <QSplitter>
#include "weather.h"




class DayliWindow : public QMainWindow
{
    Q_OBJECT

public:

    DayliWindow(QWidget *parent = nullptr);
    virtual ~DayliWindow();
    void setGraphicalElements();
    weather *mmweather{nullptr};
    QPushButton* bnthm;
    QLabel* timePlus1;
    QLabel* timePlus2;
    QLabel* timePlus3;
    QLabel* timePlus4;
    QLabel* timePlus5;
    QLabel* timePlus6;
    QLabel* timePlus7;
    QLabel* timePlus8;
    QLabel* timePlus9;
    QLabel* timePlus10;
    QLabel* timePlus11;
    QLabel* timePlus12;
    QWidget* iconPlus1;
    QWidget* iconPlus2;
    QWidget* iconPlus3;
    QWidget* iconPlus4;
    QWidget* iconPlus5;
    QWidget* iconPlus6;
    QWidget* iconPlus7;
    QWidget* iconPlus8;
    QWidget* iconPlus9;
    QWidget* iconPlus10;
    QWidget* iconPlus11;
    QWidget* iconPlus12;


public slots:

private:
    QIcon icon;
    //MainWindow *mmainwindow{nullptr};




private slots:
void bnt_d_hide();
signals:

};
#endif // DAYLIWINDOW_H
