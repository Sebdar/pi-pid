/** \file gui_test.cpp
 * \brief Shows the GUI, but no action is performed with the physical system
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std include

#include <thread>
#include <chrono>

// Qt Includes

#include <QApplication>

// Local includes

#include "gui.h"
#include "delegate_logger.h"

using namespace std::chrono_literals;

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("GUI Test");

    ControllerWindow mainWindow;
    mainWindow.resize(600, 500);
    DelegateLogger logger(static_cast<ControllerWidget*>(mainWindow.centralWidget()));

    logger.registerOrigin();
    std::this_thread::sleep_for(1us);
    logger.registerSample("test", 1.);
    
    std::this_thread::sleep_for(1us);
    logger.registerSample("test", 2.);
    
    
    mainWindow.show();
    return app.exec();
}