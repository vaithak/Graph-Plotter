#include "start_plotting.h"
#include <QtMath>
#include <QScriptEngine>
#include <QRegularExpression>

void string_mod(QString &inputted)
{

    // logarithmic , power , squareroot , absolute and exponential functions

    inputted.replace("pow","Math.pow");
    inputted.replace("sqrt","Math.sqrt");
    inputted.replace("√","Math.sqrt");
    inputted.replace("log","Math.log");
    inputted.replace("X","x");
    inputted.replace("abs","Math.abs");


    //Mathematical constants

    inputted.replace("e","Math.E");
    inputted.replace("pi","Math.PI");


    // trignometric functions

    QRegularExpression re("(?<!c)sin"); // so that arcsin doesn't become arcMath.sin
    inputted.replace(re,"Math.sin");
    inputted.replace("arcsin","Math.asin");

    re.setPattern("(?<!c)cos"); // so that arccos doesn't become arcMath.cos
    inputted.replace(re,"Math.cos");
    inputted.replace("arccos","Math.acos");

    re.setPattern("(?<!c)tan"); // so that arctan doesn't become arcMath.tan
    inputted.replace(re,"Math.tan");
    inputted.replace("arctan","Math.atan");

    re.setPattern("(?<!c)cot"); // so that arccot doesn't become arcMath.cot
    inputted.replace(re,"Math.cot");
    inputted.replace("arccot","Math.acot");


    // basic statistical functions

    inputted.replace("floor","Math.floor");
    inputted.replace("ceil","Math.ceil");
    inputted.replace("max","Math.max");
    inputted.replace("min","Math.min");

    // for replacing ^ operator with
//    QRegularExpression re("");
//    inputted.replace(re,"Math.pow");
}

void plotting_graph(QCustomPlot *customPlot, QString input_data)
{
    QScriptEngine engine;

    QVector<double> x(10001), y(10001); // initialize with entries 0..10000
    string_mod(input_data);

    // for testing user input
    qDebug()<<input_data;

    // real plotting :)
    for (int i=0; i<10001; ++i)
    {
      x[i] = i/50.0 - 100; // x goes from -100 to 100
      engine.globalObject().setProperty("x",x[i]);
      y[i] = engine.evaluate(input_data).toNumber(); // let's plot a quadratic function
    }

    // add user interactivity
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setInteraction(QCP::iSelectPlottables, true);

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setData(x, y);

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-5, 5);
    customPlot->yAxis->setRange(-5, 5);
    customPlot->replot();
}
