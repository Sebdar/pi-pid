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
    std::string dummy;

    // Input & output
    EncoderCounter input(17, 27);
    MotorDriver pwm(18);

    // Main controller
    PidController pid(5e-2, 4e-1, 4e-2);

    // Setting up the controller
    pid.setInput(&input);
    pid.setActuator(&pwm);
    
    // Getting ready for the real-time phase
    pid.init();
    pid.startAcq();

    // Set the encoder at the desired position
    std::cout << "Set the arm at the desired position, then insert a random"
                 "char & press enter\n";
    std::cin >> dummy;
    input.resetCounter();


    // Hold tight!
    std::cout << "Starting control loop !\n";
    pid.startControlLoop();


    // Update manually the set point
    // Wait for a character
    int val = 0; bool cont = true;
    while(cont) {
        std::cin >> dummy;
        try {
            val = std::stoi(dummy);
            pid.setSetPoint(val);
            std::cout << "New set point : " << val << "\n";
        } catch(...) {
            cont = false;
        }
    }
    
    pid.stopControlLoop();
    

    return 0;
}