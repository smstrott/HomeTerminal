#ifndef FORECASTWINDOW_H
#define FORECASTWINDOW_H

#include <QMainWindow>
#include <QPushButton>


class ForecastWindow : public QMainWindow
{
    Q_OBJECT

public:
    ForecastWindow(QWidget *parent = nullptr);
    virtual ~ForecastWindow();
    QPushButton* bnthm;

public slots:

private:
    QIcon icon;

private slots:
void bnt_fc_hide();
signals:

};

#endif // FORECASTWINDOW_H
