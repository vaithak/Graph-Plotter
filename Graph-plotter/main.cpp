#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <cmath>
#include <QtWidgets>
#include "qcustomplot.h"
#include "start_plotting.h"
#include <QSignalMapper>

QWidget* functions_disp()
{
    QPushButton *add = new QPushButton(QObject::tr("+"));
    QPushButton *modulo = new QPushButton(QObject::tr("%"));
    QPushButton *subtract = new QPushButton(QObject::tr("-"));
    QPushButton *multiply = new QPushButton(QObject::tr("*"));
    QPushButton *divide = new QPushButton(QObject::tr("\u2215"));
    QPushButton *sin = new QPushButton(QObject::tr("sin"));
    QPushButton *cos = new QPushButton(QObject::tr("cos"));
    QPushButton *tan = new QPushButton(QObject::tr("tan"));
    QPushButton *power2 = new QPushButton(QObject::tr("x\u00B2"));
    QPushButton *pow = new QPushButton(QObject::tr("a\u1d47"));
    QPushButton *sqrt = new QPushButton(QObject::tr("\u221A"));
    QPushButton *log = new QPushButton(QObject::tr("log"));
    QPushButton *exp = new QPushButton(QObject::tr("e"));
    QPushButton *cot = new QPushButton(QObject::tr("cot"));
    QPushButton *cosec = new QPushButton(QObject::tr("cosec"));
    QPushButton *sec = new QPushButton(QObject::tr("sec"));
    QPushButton *pi = new QPushButton(QObject::tr("\u03c0"));
    QPushButton *arctan = new QPushButton(QObject::tr("arctan"));
    QPushButton *arccos = new QPushButton(QObject::tr("arccos"));
    QPushButton *arcsin = new QPushButton(QObject::tr("arcsin"));
    QPushButton *max = new QPushButton(QObject::tr("max"));
    QPushButton *min = new QPushButton(QObject::tr("min"));
    QPushButton *floor = new QPushButton(QObject::tr("floor"));
    QPushButton *ceil = new QPushButton(QObject::tr("ceil"));
    QPushButton *abs = new QPushButton(QObject::tr("abs"));


    QGridLayout *functions = new QGridLayout();
    functions->addWidget(add,0,0,1,1);
    functions->addWidget(subtract,0,1,1,1);
    functions->addWidget(multiply,1,0,1,1);
    functions->addWidget(divide,1,1,1,1);
    functions->addWidget(modulo,2,0,1,1);
    functions->addWidget(power2,2,1,1,1);
    functions->addWidget(pow,3,0,1,1);
    functions->addWidget(sqrt,3,1,1,1);
    functions->addWidget(sin,4,0,1,1);
    functions->addWidget(cos,4,1,1,1);
    functions->addWidget(tan,5,0,1,1);
    functions->addWidget(sec,5,1,1,1);
    functions->addWidget(cosec,6,0,1,1);
    functions->addWidget(cot,6,1,1,1);
    functions->addWidget(arcsin,7,0,1,1);
    functions->addWidget(arccos,7,1,1,1);
    functions->addWidget(arctan,8,0,1,1);
    functions->addWidget(floor,8,1,1,1);
    functions->addWidget(ceil,9,0,1,1);
    functions->addWidget(max,9,1,1,1);
    functions->addWidget(min,10,0,1,1);
    functions->addWidget(abs,10,1,1,1);
    functions->addWidget(exp,11,0,1,1);
    functions->addWidget(pi,11,1,1,1);

    functions->setHorizontalSpacing(0);
    functions->setVerticalSpacing(0);
    QWidget *function_widget = new QWidget();
    function_widget->setLayout(functions);
    return function_widget;
}

void MainWindow::on_plot_button_clicked()
{
    qDebug()<<(input->text());
    plotting_graph(customplot,input->text());

}

int main(int argc, char *argv[])
{
   // setting the size of application
    QApplication a(argc, argv);
    QDesktopWidget dw;
    int x = dw.width()*0.9;
    int y = dw.height()*0.9;
    MainWindow window;
    window.setFixedSize(x,y);

    // preparing the functions layout
    QWidget *function_widget=new QWidget();
    function_widget=functions_disp();

    // line-edit and qwidget layout
    window.input->setFixedHeight(40);
    window.input->setStyleSheet("font-size:30px");
    QPushButton *plot_button = new QPushButton("  Start Plotting  ");
    plot_button->setStyleSheet("background-color:#7cfc60;");

    // sending data to plotting function
    QObject::connect(plot_button, SIGNAL(clicked(bool)) ,&window, SLOT(on_plot_button_clicked()));

    QVBoxLayout *plot = new QVBoxLayout();
    plot->addWidget(window.input);
    plot->addWidget(plot_button);
    plot->addWidget(window.customplot);
    plot->setAlignment(plot_button,Qt::AlignRight);

    QWidget *rightpart = new QWidget();
    rightpart->setLayout(plot);

    QGridLayout *full_screen = new QGridLayout();
    full_screen->addWidget(function_widget,0,0,5,2);
    full_screen->addWidget(rightpart,0,4,20,8);

    QWidget *display = new QWidget();
//    display->setStyleSheet("background-color:black");
    display->setLayout(full_screen);
    window.setCentralWidget(display);

    window.setStyleSheet("QWidget {"
                         "background-color:black;"
                         "}"

                         "QPushButton {"
                         "background-color:white;"
                         "min-width:30px;"
                         "min-height:40px;"
                         "font-size:18px;"
                         "border:1px solid;"
                         "font-family:Sans-Serif"
                         "}"

                         "QPushButton:hover {"
                         "border:3px solid black;"
                         "background-color:#00ff00"
                         "}"

                         "QPushButton:pressed {"
                         "border:5px solid black;"
                         "}"

                         "QLabel {"
                         "background-color:white;"
                         "}"

                         "QLineEdit {"
                         "background-color:white;"
                         "}"

                         );
    window.show();
    return a.exec();
}