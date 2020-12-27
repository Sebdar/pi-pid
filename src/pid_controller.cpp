/** \file pid_controller.cpp
 * \brief PID Dontroller definition
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <functional>
#include <iostream>

// Local includes

#include "pid_controller.h"

// --------------------------   PidController  ----------------------------- //

int PidController::init() {
    if(sampler == nullptr) {
        throw std::runtime_error("Sampler is not defined");
    } else if(actuator == nullptr) {
        throw std::runtime_error("Actuator is not defined");
    }

    sampler->init();
    actuator->init();
    return 0;
}

int PidController::startAcq() {
    sampler->startAcq();
    return 0;
}

int PidController::stopAcq() {
    //Nothing to do
    return 0;
}

int PidController::startControlLoop() {
    cont = true;
    loopThread = new std::thread(&PidController::controlLoop, this);
    if(!loopThread->joinable()) {
        // Could not start thread
        return -1;
    } else {
        return 0;
    }
}

void PidController::controlLoop() {
    // Here comes the fun : the actual control loop of the PID
    double sample, last_y, y, out;
    double integrator;

    last_y = sampler->getSample();

    while(cont) {
        // Refresh sample
        sample = sampler->getSample();
        y = setPoint - sample; // Difference between set point and value

        // Integrator update
        integrator += y / (delay.count() / 1e6);

        out =   y * settings.p;
        out += (y - last_y) / (delay.count() / 1e6) * settings.d;
        out +=  integrator * settings.i;
        // TODO : Derivative and Integral action

        actuator->setOutput(out);
        std::this_thread::sleep_for(delay);
        std::cout << "Sample : " << sample
                  << "\nOut : " << out << "\n\n";
    }
}

int PidController::stopControlLoop() {
    if(loopThread == nullptr || !loopThread->joinable()) {
        // Thread was not created in the first place
        return -1;
    }

    cont = false;
    loopThread->join();
    delete loopThread;
    loopThread = nullptr;
    return 0;
}