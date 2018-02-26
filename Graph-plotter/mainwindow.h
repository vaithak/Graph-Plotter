#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLineEdit *input = new QLineEdit();
    QCustomPlot *customplot = new QCustomPlot();
    QWidget* functions_disp();

public slots:
        void on_plot_button_clicked();
        void function_clicked();
    };

#endif // MAINWINDOW_H
