/** \file gui.h
 * \brief Main window & widgets declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef GUI_H
#define GUI_H

// Qt includes

#include <QMainWindow>
#include <QGridLayout>
#include <QtCharts>


// Forward declaration

class DelegateLogger;

/** \class ControllerWidget
 * \brief The center widget w/ graph and controls
 */
class ControllerWidget : public QWidget {
    Q_OBJECT

public:

    ControllerWidget(QWidget* parent = nullptr);
    virtual ~ControllerWidget() override;

    void setLogger(DelegateLogger* _l) {logger = _l;}

    void setMaxSecondsShown(int sec) {maxDiff = sec;}

    void setYRange(float min, float max);

public Q_SLOTS:
    void slotSeriesUpdated(const QString name);

private:
    // QChart pointers
    QGridLayout* controllerLayout;
    QChart* chart1;
    QLineSeries* samples;
    QChartView* chartView1;
    QValueAxis* axisX, *axisY;
    
    DelegateLogger* logger;
    
    /** \brief Maximum time difference (in seconds) between the first and last
     * points
     */
    int maxDiff = 5;

    /** \brief Y axis limits
     */
    float minY = -1., maxY = 1.;
};


/** \class ControllerWindow
 * \brief The GUI main inteface
 */
class ControllerWindow : public QMainWindow {
    Q_OBJECT
public :
    // Constructor and destructor
    ControllerWindow(QWidget* parent = nullptr);
    virtual ~ControllerWindow() override;

private:
    QWidget* centerWidget;
};



#endif
