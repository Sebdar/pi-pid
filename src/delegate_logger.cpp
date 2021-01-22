/** \file delegate_logger.cpp
 * \brief Data logger class definition
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */
#include <iostream>
// Local includes

#include "delegate_logger.h"

DelegateLogger::DelegateLogger(ControllerWidget* _controller)
        : widget(_controller) 
{
    if(widget != nullptr) {
        connect(this, SIGNAL(updatedSeries(const QString&)),
                widget, SLOT(slotSeriesUpdated(const QString&)),
                Qt::QueuedConnection
        );
        widget->setLogger(this);
    }

    moveToThread(new QThread);
    
}

void DelegateLogger::registerOrigin() {
    originStamp = std::chrono::steady_clock::now();
}

void DelegateLogger::registerSample(const std::string& name, double value) {
    std::chrono::time_point<std::chrono::steady_clock> now 
        = std::chrono::steady_clock::now();
    std::chrono::microseconds timestamp = 
        std::chrono::duration_cast<std::chrono::microseconds>(now - originStamp);

    // Insert time stamp + value as a point
    sampleMap[name].push_back(QPointF((float) timestamp.count() / (float) 1e6, 
                                      value));
    for(const auto& point : sampleMap[name]) {
        std::cout << point.x() << " - " << point.y() << '\n';
    }
    // Notify the GUI widget
    Q_EMIT(updatedSeries(QString::fromStdString(name)));
    
    return;
}

QVector<QPointF>* DelegateLogger::getPointSeries(const std::string& name) {
    try {
        auto& vec = sampleMap.at(name);
        return &vec;
    } catch(std::exception& e) {
        // Failed to retrieve the vector
        return nullptr;
    }
}
