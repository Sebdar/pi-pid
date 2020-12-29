/** \file simple_pid.cpp
 * \brief A simple PID controller test
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <iostream>

// Local includes

#include "motor_driver.h"
#include "encoder_counter.h"
#include "pid_controller.h"


int main() {
    char dummy;
    EncoderCounter input(17, 27);
    MotorDriver pwm(18);

    PidController pid(5e-2, 4e-1, 2e-2);

    pid.setInput(&input);
    pid.setActuator(&pwm);
    
    pid.init();
    pid.startAcq();

    // Set the encoder at the desired position
    std::cout << "Set the arm at the desired position, then press enter\n";
    std::cin >> dummy;

    input.resetCounter();

    std::cout << "Starting control loop !\n";

    pid.startControlLoop();

    // Wait for a character
    std::cin >> dummy;

    pid.stopControlLoop();
    

    return 0;
}