/** \file pid_controller.cpp
 * \brief PID Dontroller definition
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <functional>
#include <iostream>
#include <cmath>

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
    double integrator = 0;

    double d = 0, last_d = 0; // Decay for derivative low-pass

    last_y = sampler->getSample();

    while(cont) {
        // Refresh sample
        sample = sampler->getSample();
        y = setPoint - sample; // Difference between set point and value

        // Integrator update

        /// Proportionnal action
        out =  y * settings.p;

        /// Derivative action
        d = (y - last_y) / ( ((double) delay.count()) / 1e6);
        double cum_d = (decay * d  + (1 - decay) * last_d);
        out += cum_d * settings.d;
        
        /// Integral action
        if((integrator < integratorUpper && integrator > integratorLower) 
            || integrator * y <= 0) {
            // Add to the integrator if it hasn't exceeded a certain value or 
            // it could diminish (if integrator and sample don't have the same
            // sign)
            integrator += y * ( (double) delay.count() / 1e6);
        }
        out += integrator * settings.i;

        // Output order
        actuator->setOutput(out);
        std::cout << "Sample : " << sample
                  << "\nOut : " << out
                  << " p : " << y*settings.p << "  i : " << integrator
                  << " d : " << cum_d << "\n\n";

        // Loop wait
        std::this_thread::sleep_for(delay);
        
        // Prepare for next sample
        last_d = cum_d;
        last_y = y;
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

void PidController::setIntegratorBounds(double lower, double upper) noexcept {
    integratorLower = lower;
    integratorUpper = upper;
}