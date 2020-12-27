/** \file motor_driver.cpp
 * \brief Motor driver (output) class definition
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <cmath>

// Local includes

#include <wiringPi.h>
#include "motor_driver.h"


// -------------------------- Static Functions ----------------------------- //

int MotorDriver::wrapCycleToPWM(double cycleDuty) {
    if(cycleDuty > 1) cycleDuty = 1;
    if(cycleDuty < -1) cycleDuty = -1;

    return std::floor(25.6 * cycleDuty + 76.8);
}

double MotorDriver::wrapPWMToDouble(int pwm) {
    return (pwm - 76.8) / 25.6;
}

// --------------------------    MotorDriver   ----------------------------- //

MotorDriver::MotorDriver(int _pin) : pin(_pin), command(0) {
}

int MotorDriver::init() {
    wiringPiSetupGpio();
    pinMode(pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(1024);
    pwmSetClock(375); // 50 Hz; base clock is 19,2 MHz
    
    return 0;
}

int MotorDriver::setOutput(const double cycleDuty) {
    pwmWrite(pin, wrapCycleToPWM(cycleDuty));
    return 0;
}

