/** \file first_order_simu.cpp
 * \brief Shows a step response from a simulated first order system
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
#include "simu/firstorder.h"

using namespace std::chrono_literals;

void threadLoop(DelegateLogger& logger) {
    FirstOrder system(0.9);
    system.setOutput(1.);

    for(;;) {
        logger.registerSample("test", system.getSample());
        std::this_thread::sleep_for(50ms);
    }
}

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Step response");

    ControllerWindow mainWindow;
    mainWindow.resize(600, 500);
    DelegateLogger logger(static_cast<ControllerWidget*>(mainWindow.centralWidget()));

    logger.registerOrigin();

    auto thread = new std::thread([&] () {threadLoop(logger);}); 

    mainWindow.show();
    return app.exec();
}

