/** \file motor_driver.h
 * \brief Motor driver (output) class declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// Local includes

#include "output.h"

class MotorDriver : public Output {
public:
    // Constructor and destructor
    MotorDriver(const int pin);
    ~MotorDriver() override {};

    // Overridden methods
    int init() override;
    int setOutput(const double cycleDuty) override;
    double getCurrentOutput() override {return wrapPWMToDouble(command);}
    int close() override {return 0;}


    // Motor driver specific methods
    // PWM handling
    /** \fn wrapCycleToPWM
     * \brief Wrap controller-style cycle duty (double) to wiringPi-style pwm
     * output (int)
     */
    inline static int wrapCycleToPWM(double cycleDuty);
    
    /** \fn wrapPWMToDouble
     * \brief Wrap wiringPi-style pwm output (int) to controller-style cycle 
     * duty (double)
     */
    inline static double wrapPWMToDouble(int pwm);

private:
    int command;
    const int pin;
};

#endif
