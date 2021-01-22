/** \file gui.h
 * \brief Main window & widgets declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <iostream>

// Local includes

#include "gui.h"
#include "delegate_logger.h"


// -------------------------- ControllerWindow ----------------------------- //

ControllerWindow::ControllerWindow(QWidget* parent) : QMainWindow(parent) {
    centerWidget = new ControllerWidget(this);
    setCentralWidget(centerWidget);
}

ControllerWindow::~ControllerWindow() {
    delete centerWidget;
}


// -------------------------- ControllerWidget ----------------------------- //

ControllerWidget::ControllerWidget(QWidget* parent) : QWidget(parent) {
    controllerLayout = new QGridLayout(this);

    samples = new QLineSeries;
    samples->append(0, 0);

    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setRange(0, maxDiff);
    axisY->setRange(minY, maxY);

    chart1 = new QChart;
    chart1->legend()->hide();
    chart1->addSeries(samples);
    chart1->createDefaultAxes();
    chart1->setTitle("Input value");
    chart1->setAxisX(axisX, samples);
    chart1->setAxisY(axisY, samples);

    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    controllerLayout->addWidget(chartView1, 1, 1);
}

ControllerWidget::~ControllerWidget() {
    delete controllerLayout;
}

void ControllerWidget::slotSeriesUpdated(const QString name) {
    if(name == "test") {
        std::cout << "Received test sample\n";
        
        auto& pt = logger->getPointSeries(name.toStdString())->back();
        samples->append(pt);
        
        // If we exceeded the max number of pts : remove the first one
        if(pt.x() - samples->at(0).x() > maxDiff) {
            samples->remove(0);
            axisX->setRange(samples->at(0).x(), pt.x());
        }
        if(pt.y() > maxY) {setYRange(minY, pt.y());}
        else if(pt.y() < minY) {setYRange(pt.y(), maxY);}

        chartView1->repaint();
    }
}

void ControllerWidget::setYRange(float min, float max) {
    minY = min;
    maxY = max;
    axisY->setRange(min, max);
}
