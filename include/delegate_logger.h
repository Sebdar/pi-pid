/** \file delegate_logger.h
 * \brief Data logger class declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef DELEGATE_LOGGER_H
#define DELEGATE_LOGGER_H

// Std include

#include <string>
#include <unordered_map>
#include <chrono>

// Qt includes

#include <QObject>
#include <QString>
#include <QVector>
#include <QPointF>

// local includes

#include "gui.h" 

/** \class DelegateLogger
 * \brief The DelegateLogger class serves as an interface between the
 * controller & its samples and the plot or file saving device. It is also an
 * adapter between the C++ std and the Qt framework / event-driven programming
 */
class DelegateLogger : public QObject {
    Q_OBJECT
public:
    // Constructor and destructor
    DelegateLogger(ControllerWidget* _controller = nullptr);
    ~DelegateLogger() {}

    // ---- Controller (std) interface ---- //

    /** \fn registerSample
     * \brief Saves the current sample (with the current time) in thee inner
     * vectors of the Logger. This happens rather quickly.
     */
    void registerSample(const std::string& name, double value);

    /** \fn registerOrigin
     * \brief Registers the origin timestamp ("t = 0") as the current time.
     * To be called at the beginning of the experiment
     */
    void registerOrigin();

    // ---- GUI interface ---- //
    
    /** \fn getPointSeries
     * \brief Returns a pointer to a point series. Returns nullptr
     * if it does not exist.
     */
    QVector<QPointF>* getPointSeries(const std::string& name);

Q_SIGNALS:
    void updatedSeries(const QString seriesName);

private:
    std::chrono::time_point<std::chrono::steady_clock> originStamp;
    ControllerWidget* widget;
    std::unordered_map<std::string, QVector<QPointF>> sampleMap;
};

#endif
