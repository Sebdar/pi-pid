/** \file encoder_counter.cpp
 * \brief Incremental encoder handler class
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <functional>

// Local includes

#include <wiringPi.h>
#include "encoder_counter.h"

// Debug
#ifdef PRINT_ENCODER
#   include <iostream>
#endif

// Global variables
// Ugh.. I hate this but the wiringPi library only allows C-style functions
// pointers that WON'T TAKE ANY ARGUMENT ... we are forced to use these ugly
// global variables
static EncoderCounter* ptr = nullptr;

void callbackA() {
    ptr->threadCallback(ptr->getPinA());
}

void callbackB() {
    ptr->threadCallback(ptr->getPinB());
}

EncoderCounter::EncoderCounter(const int _a, const int _b)
    : pinA(_a), pinB(_b) {
    ptr = this;
}

EncoderCounter::~EncoderCounter() {
    ptr = nullptr;
}

int EncoderCounter::init() {
    wiringPiSetupGpio();
    return 0;
}

void EncoderCounter::threadCallback(const int pin) {
    int oldA = stateA;
    int oldB = stateB;
    
    // register new inputs
    if(pin == pinA) {
        stateA = digitalRead(pinA);
    } else if(pin == pinB) {
        stateB = digitalRead(pinB);
    } else {return;}

    // State handling
    switch(state) {
        case 0:
            if(oldA == LOW && stateA == HIGH) {
                state = 1;
            } else if(oldB == LOW && stateB == HIGH) {
                state = 3;
                counterValue--;
#ifdef PRINT_ENCODER
                std::cout << counterValue << std::endl;
#endif
            }
            break;
        case 1:
            if(oldB == LOW && stateB == HIGH) {
                state = 2;
            } else if(oldA == HIGH && stateA == LOW) {
                state = 0;
            }
            break;
        case 2:
            if(oldA == HIGH && stateA == LOW) {
                state = 3;
            } else if(oldB == HIGH && stateB == LOW) {
                state = 1;
            }
            break;
        case 3:
            if(oldB == HIGH && stateB == LOW) {
                state = 0;
                counterValue++;
#ifdef PRINT_ENCODER
                std::cout << counterValue << std::endl;
#endif
            } else if(oldA == LOW && stateA == HIGH) {
                state = 2;
            }
            break;
    }

}

int EncoderCounter::startAcq() {
    wiringPiISR(pinA, INT_EDGE_BOTH, &callbackA);
    wiringPiISR(pinB, INT_EDGE_BOTH, &callbackB);
    
    return 0;
}
