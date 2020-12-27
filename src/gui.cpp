/** \file gui.h
 * \brief Main window & widgets declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#include "gui.h"


// -------------------------- ControllerWindow ----------------------------- //

ControllerWindow::ControllerWindow(QWidget* parent) : QMainWindow(parent) {
    centerWidget = new ControllerWidget(this);
}

ControllerWindow::~ControllerWindow() {
    delete centerWidget;
}


// -------------------------- ControllerWidget ----------------------------- //

ControllerWidget::ControllerWidget(QWidget* parent) : QWidget(parent) {
    controllerLayout = new QGridLayout(this);
}

ControllerWidget::~ControllerWidget() {
    delete controllerLayout;
}