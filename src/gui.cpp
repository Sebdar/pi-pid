/** \file gui.h
 * \brief Main window & widgets declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

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
    samples = new QLineSeries();
    chart1 = new QChart;
    chart1->legend()->hide();
    chart1->addSeries(samples);
    chart1->createDefaultAxes();
    chart1->setTitle("Input value");
    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    controllerLayout->addWidget(chartView1, 1, 1);
}

ControllerWidget::~ControllerWidget() {
    delete controllerLayout;
}

void ControllerWidget::slotSeriesUpdated(const QString name) {
    if(name == "test") {
        samples->replace(*logger->getPointSeries(name.toStdString()));
        chartView1->repaint();
    }
}
