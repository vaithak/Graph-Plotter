#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLineEdit* input1 = new QLineEdit();
    QLineEdit* input2 = new QLineEdit();
    QCustomPlot *customplot = new QCustomPlot();
    QWidget* functions_disp();
    QPushButton* status= new QPushButton("+");
    QWidget* second_input = new QWidget();
    int flag;
    MainWindow()
    {
        flag=0;
    }

public slots:
        void on_plot_button_clicked();
        void function_clicked();
        void on_status_clicked();
    };

#endif // MAINWINDOW_H
