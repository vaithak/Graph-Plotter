#include "start_plotting.h"
#include <QtMath>
#include <QScriptEngine>
#include <QRegularExpression>

void string_mod(QString &inputted1 , QString &inputted2)
{

    // logarithmic , power , squareroot , absolute and exponential functions

    inputted1.replace("pow","Math.pow");
    inputted1.replace("sqrt","Math.sqrt");
    inputted1.replace("√","Math.sqrt");
    inputted1.replace("log","Math.log");
    inputted1.replace("X","x");
    inputted1.replace("abs","Math.abs");

    inputted2.replace("pow","Math.pow");
    inputted2.replace("sqrt","Math.sqrt");
    inputted2.replace("√","Math.sqrt");
    inputted2.replace("log","Math.log");
    inputted2.replace("X","x");
    inputted2.replace("abs","Math.abs");

    //Mathematical constants

    QRegularExpression re("(?<![sc])e");
    inputted1.replace(re,"Math.E");
    inputted1.replace("pi","Math.PI");
    inputted1.replace("π","Math.PI");

    inputted2.replace(re,"Math.E");
    inputted2.replace("pi","Math.PI");
    inputted2.replace("π","Math.PI");

    // trignometric functions

    re.setPattern("cosec\(([^)]+)\)");
    inputted1.replace(re,"1/(sin\\1)");
    inputted2.replace(re,"1/(sin\\1)");

    re.setPattern("sec\(([^)]+)\)");
    inputted1.replace(re,"1/(cos\\1)");
    inputted2.replace(re,"1/(cos\\1)");

    re.setPattern("(?<!c)sin"); // so that arcsin doesn't become arcMath.sin
    inputted1.replace(re,"Math.sin");
    inputted1.replace("arcsin","Math.asin");
    inputted2.replace(re,"Math.sin");
    inputted2.replace("arcsin","Math.asin");

    re.setPattern("(?<!c)cos"); // so that arccos doesn't become arcMath.cos
    inputted1.replace(re,"Math.cos"); // also works for cosecant funcion
    inputted1.replace("arccos","Math.acos");
    inputted2.replace(re,"Math.cos");
    inputted2.replace("arccos","Math.acos");

    re.setPattern("(?<!c)tan"); // so that arctan doesn't become arcMath.tan
    inputted1.replace(re,"Math.tan");
    inputted1.replace("arctan","Math.atan");
    inputted2.replace(re,"Math.tan");
    inputted2.replace("arctan","Math.atan");

    re.setPattern("(?<!c)cot"); // so that arccot doesn't become arcMath.cot
    inputted1.replace(re,"Math.cot");
    inputted1.replace("arccot","Math.acot");
    inputted2.replace(re,"Math.cot");
    inputted2.replace("arccot","Math.acot");


    // basic statistical functions

    inputted1.replace("floor","Math.floor");
    inputted1.replace("ceil","Math.ceil");
    inputted1.replace("max","Math.max");
    inputted1.replace("min","Math.min");

    inputted2.replace("floor","Math.floor");
    inputted2.replace("ceil","Math.ceil");
    inputted2.replace("max","Math.max");
    inputted2.replace("min","Math.min");

    // for replacing ^ operator with
//    QRegularExpression re("");
//    inputted.replace(re,"Math.pow");
}

void plotting_graph(QCustomPlot *customPlot, QString input_data_1, QString input_data_2)
{
    QScriptEngine engine;
    customPlot->clearGraphs();

    QVector<double> x1(20001),y1(20001),x2(20001),y2(20001); // initialize with entries 0..10000
    string_mod(input_data_1,input_data_2);

    // for intersection points
    QVector<double> xint,yint;
    xint.clear();
    yint.clear();

    // for testing user input
    qDebug()<<input_data_1<<input_data_2;

    // making x-Axis and y-Axis
    QVector<double> xx(2),xy(2,0),yx(2,0),yy(2);

    if(input_data_1!="" || input_data_2!="")
    {
        xx[0]=-500000;
        xx[1]=500000;
        yy[0]=500000;
        yy[1]=-500000;

        // x-Axis
        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::black,0.6));
        customPlot->graph(0)->setData(xx,xy);

        // y-Axis
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::black,0.6));
        customPlot->graph(1)->setData(yx,yy);
    }

    // real plotting :)
    if(input_data_1!="")
    {
        for (int i=0; i<20001; ++i)
        {
            x1[i] = i/100.0 - 100; // x goes from -100 to 100
            engine.globalObject().setProperty("x",x1[i]);
            y1[i] = engine.evaluate(input_data_1).toNumber(); // let's plot a quadratic function

            // marking the intersection points
            if(abs(y1[i]-0)<0.015)
            {
                xint.push_back(x1[i]);
                yint.push_back(y1[i]);
            }
            else if(x1[i]==0)
            {
                xint.push_back(x1[i]);
                yint.push_back(y1[i]);
            }
        }

        // create graph and assign data to it:
        customPlot->addGraph();
        customPlot->graph(2)->setPen(QPen(Qt::red,2));
        customPlot->graph(2)->setData(x1, y1);
    }
    if(input_data_2!="")
    {
       for (int i=0; i<20001; ++i)
        {
            x2[i] = i/100.0 - 100; // x goes from -100 to 100
            engine.globalObject().setProperty("x",x2[i]);
            y2[i] = engine.evaluate(input_data_2).toNumber(); // let's plot a quadratic function

            // marking the intersection points
            if(abs(y2[i]-0)<0.015)
            {
                xint.push_back(x2[i]);
                yint.push_back(y2[i]);
            }
            else if(x2[i]==0)
            {
                xint.push_back(x2[i]);
                yint.push_back(y2[i]);
            }
            else if(abs(y1[i]-y2[i])<0.015)
            {
                xint.push_back(x2[i]);
                yint.push_back(y2[i]);
            }
        }

       // create second graph and assign data to it:
       customPlot->addGraph();

       // so that graph index doesn't go out of bound
       if(input_data_1=="")
       {
           customPlot->graph(2)->setPen(QPen(Qt::green,2));
           customPlot->graph(2)->setData(x2, y2);
       }
       else
       {
           customPlot->graph(3)->setPen(QPen(Qt::green,2));
           customPlot->graph(3)->setData(x2, y2);
       }
    }

    // plotting the intersection graph
    if(input_data_1!=""  && input_data_2!="")
    {
        customPlot->addGraph();
        customPlot->graph(4)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(4)->setScatterStyle(QCPScatterStyle::ssCircle);
        customPlot->graph(4)->setData(xint,yint);
        customPlot->graph(4)->setPen(QPen(Qt::gray,4));
    }
    else if(input_data_1!="" || input_data_2!="")
    {
        customPlot->addGraph();
        customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssCircle);
        customPlot->graph(3)->setData(xint,yint);
        customPlot->graph(3)->setPen(QPen(Qt::gray,4));
    }

    // add user interactivity
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setInteraction(QCP::iSelectPlottables, true);

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-5, 5);
    customPlot->yAxis->setRange(-5, 5);
    customPlot->replot();
}
