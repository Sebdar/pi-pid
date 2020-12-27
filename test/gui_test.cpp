/** \file gui_test.cpp
 * \brief Shows the GUI, but no action is performed with the physical system
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Qt Includes

#include <QApplication>

// Local includes

#include "gui.h"

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("GUI Test");

    ControllerWindow mainWindow;

    mainWindow.show();
    return app.exec();
}