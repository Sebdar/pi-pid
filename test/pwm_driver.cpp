/** \file pwm_driver.cpp
 * \brief PWM cycle unit test (motor driver class)
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

// Local includes
#include "motor_driver.h"

int main() {
    MotorDriver pwm(18);

    pwm.init();
    
    while(1){
        for(double i = -1; i < 1; i+= 0.05) {
            std::cout << i << '\n';
            pwm.setOutput(i);
            std::this_thread::sleep_for(200ms);
        }
        std::this_thread::sleep_for(400ms);
    }
}