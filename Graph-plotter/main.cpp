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

QWidget* MainWindow::functions_disp()
{
    QLabel *func_head = new QLabel("   Functions :-   ");
    func_head->setStyleSheet("font-style:italic");

    QPushButton *add = new QPushButton(QObject::tr("+"));
    QPushButton *modulo = new QPushButton(QObject::tr("%"));
    QPushButton *subtract = new QPushButton(QObject::tr("-"));
    QPushButton *multiply = new QPushButton(QObject::tr("*"));
    QPushButton *divide = new QPushButton(QObject::tr("\u2215"));
    QPushButton *sin = new QPushButton(QObject::tr("sin"));
    QPushButton *cos = new QPushButton(QObject::tr("cos"));
    QPushButton *tan = new QPushButton(QObject::tr("tan"));
    QPushButton *pow = new QPushButton(QObject::tr("pow"));
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
    QPushButton *open = new QPushButton(QObject::tr("("));
    QPushButton *closed = new QPushButton(QObject::tr(")"));

    QGridLayout *functions = new QGridLayout();
    functions->addWidget(func_head,0,0,1,2);
    functions->addWidget(add,1,0,1,1);
    functions->addWidget(subtract,1,1,1,1);
    functions->addWidget(multiply,2,0,1,1);
    functions->addWidget(divide,2,1,1,1);
    functions->addWidget(modulo,3,0,1,1);
    functions->addWidget(pow,3,1,1,1);
    functions->addWidget(sqrt,4,0,1,1);
    functions->addWidget(sin,4,1,1,1);
    functions->addWidget(cos,5,0,1,1);
    functions->addWidget(tan,5,1,1,1);
    functions->addWidget(sec,6,0,1,1);
    functions->addWidget(cosec,6,1,1,1);
    functions->addWidget(cot,7,0,1,1);
    functions->addWidget(arcsin,7,1,1,1);
    functions->addWidget(arccos,8,0,1,1);
    functions->addWidget(arctan,8,1,1,1);
    functions->addWidget(floor,9,0,1,1);
    functions->addWidget(ceil,9,1,1,1);
    functions->addWidget(max,10,0,1,1);
    functions->addWidget(min,10,1,1,1);
    functions->addWidget(abs,11,0,1,1);
    functions->addWidget(exp,11,1,1,1);
    functions->addWidget(pi,12,0,1,1);
    functions->addWidget(log,12,1,1,1);
    functions->addWidget(open,13,0,1,1);
    functions->addWidget(closed,13,1,1,1);

    functions->setHorizontalSpacing(0);
    functions->setVerticalSpacing(0);

    // adding signals and slots to buttons
    QObject::connect(sin,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(cos,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(add,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(multiply,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(divide,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(sqrt,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(pi,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(exp,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(pow,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(max,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(min,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(abs,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(log,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(floor,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(modulo,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(subtract,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(tan,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(sec,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(cosec,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(cot,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(arctan,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(arcsin,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(arccos,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(ceil,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(open,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));
    QObject::connect(closed,SIGNAL(clicked(bool)),this,SLOT(function_clicked()));


    // adding buttons into layout and finally into a widget
    QWidget *function_widget = new QWidget();
    function_widget->setLayout(functions);
    return function_widget;
}

void MainWindow::function_clicked()
{
    QPushButton *press = (QPushButton*) sender();
    QLineEdit* current = qobject_cast<QLineEdit*>(this->focusWidget());
    if(current!=0)
    {
        if(press->text() == '(' || press->text() == ')' || press->text()=="π" || press->text()=="e")
        {
            current->insert(press->text());
        }
        else if(press->text() == "+" || press->text() == "%" || press->text() == "*" || press->text() == "-")
        {
            current->insert(press->text());
        }
        else
        {
            current->insert(press->text() + '(');
        }
    }
}

void MainWindow::on_status_clicked()
{
    this->flag=(this->flag)^1;
    if(this->flag == 1)
    {
        this->second_input->show();
        this->input2->setFocus();
        this->status->setStyleSheet("min-width:50px;max-width:50px;background-color:red;font-style:none");
        this->status->setText("X");
    }
    else
    {
        this->input1->setFocus();
        this->second_input->close();
        this->input2->clear();
        plotting_graph(this->customplot,this->input1->text(),this->input2->text());
        this->status->setText("+");
        this->status->setStyleSheet("min-width:50px;max-width:50px;background-color:green;font-style:bold");
    }
}

void MainWindow::on_plot_button_clicked()
{
    qDebug()<<(this->input1->text())<<(this->input2->text());
    plotting_graph(this->customplot,this->input1->text(),this->input2->text());
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
    window.status->setStyleSheet("background-color:green");

    // preparing the functions layout
    QWidget *function_widget=new QWidget();
    function_widget=window.functions_disp();

    // line-edit and qwidget layout
    window.input1->setFixedHeight(40);
    window.input1->setStyleSheet("font-size:30px");
    window.input2->setFixedHeight(40);
    window.input2->setStyleSheet("font-size:30px");
    QPushButton *plot_button = new QPushButton("  Start Plotting  ");
    plot_button->setStyleSheet("background-color:#7cfc60;");

    // sending data to plotting function
    QObject::connect(plot_button, SIGNAL(clicked(bool)) ,&window, SLOT(on_plot_button_clicked()));

    // first input
    QHBoxLayout* first_input_layout = new QHBoxLayout();
    QLabel* f1x = new QLabel(" \u0192\u2081(x) = ");
    f1x->setFixedHeight(45);
    first_input_layout->addWidget(f1x);
    first_input_layout->addWidget(window.input1);
    first_input_layout->addWidget(window.status);
    first_input_layout->setMargin(0);
    QWidget* first_input = new QWidget();
    first_input->setLayout(first_input_layout);
    first_input->setFixedHeight(60);


    // second input
    QHBoxLayout* second_input_layout = new QHBoxLayout();
    QLabel* f2x = new QLabel(" \u0192\u2082(x) = ");
    f2x->setFixedHeight(45);
    second_input_layout->addWidget(f2x);
    second_input_layout->addWidget(window.input2);
    second_input_layout->setMargin(0);
    window.second_input->setLayout(second_input_layout);
    window.second_input->setFixedHeight(60);

    QVBoxLayout *plot = new QVBoxLayout();
    plot->addWidget(first_input);
    plot->addWidget(window.second_input);
    plot->addWidget(plot_button);
    plot->addWidget(window.customplot);
    plot->setAlignment(plot_button,Qt::AlignRight);

    // for dynamic appearance or closing of second input;
    QObject::connect(window.status,SIGNAL(clicked(bool)),&window,SLOT(on_status_clicked()));

    QWidget *rightpart = new QWidget();
    rightpart->setLayout(plot);

    QGridLayout *full_screen = new QGridLayout();
    full_screen->addWidget(function_widget,0,0,5,2);
    full_screen->addWidget(rightpart,0,4,20,8);

    window.second_input->close();

    QWidget *display = new QWidget();
    display->setLayout(full_screen);
    window.setCentralWidget(display);
    window.setStyleSheet("QWidget {"
                         "background-color:black;"
                         "}"

                         "QPushButton{"
                         "background-color:white;"
                         "min-width:129px;"
                         "min-height:37px;"
                         "max-width:129px;"
                         "max-height:37px;"
                         "font-size:18px;"
                         "border:1px solid;"
                         "font-family:Sans-Serif;"
                         "font-style:italic"
                         "}"

                         "QPushButton:hover {"
                         "border:3px solid black;"
                         "background-color:#00ff00"
                         "}"

                         "QPushButton:pressed {"
                         "border:5px solid black;"
                         "}"

                         "QLabel {"
                         "background-color:#00f1ff;"
                         "min-height:30px;"
                         "font-size:25px;"
                         "color:black;"
                         "margin:0px;"
                         "}"

                         "QLineEdit {"
                         "background-color:white;"
                         "}"

                         );

    window.status->setStyleSheet("min-width:50px;max-width:50px;background-color:green;font-style:bold");

    window.show();
    return a.exec();
}
