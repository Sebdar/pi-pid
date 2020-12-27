/** \file gui.h
 * \brief Main window & widgets declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QGridLayout>


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

/** \class ControllerWidget
 * \brief The center widget w/ graph and controls
 */
class ControllerWidget : public QWidget {
    Q_OBJECT
public:
    ControllerWidget(QWidget* parent = nullptr);
    virtual ~ControllerWidget() override;
private:
    QGridLayout* controllerLayout;

};


#endif
