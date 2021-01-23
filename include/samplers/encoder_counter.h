/** \file encoder_counter.h
 * \brief Incremental encoder handler class declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef ENCODER_COUNTER_H
#define ENCODER_COUNTER_H

// Std includes

#include <thread>
#include <atomic>

// Local includes

#include "sampler.h"

class EncoderCounter : public Sampler {
public:
    // Constructor and destructor
    EncoderCounter(const int pinA, const int pinB);
    ~EncoderCounter() override;

    // Overridden methods
    virtual int init() override;
    virtual int startAcq() override;
    virtual double getSample() override {return (double) counterValue / 4.;}
    virtual int close() override {return 0;}

    // Encoder specific functions

    /** \fn getPinA
     */
    inline int getPinA() const {return pinA;}
    
    /** \fn getPinB
     */
    inline int getPinB() const {return pinB;}

    /** \fn threadCallback
     * \brief Handles an interrupt. Because of the way interrupt are handled in
     * wiringPi, this method is called by static C functions in 
     * encoder_counter.cpp
     */
    void threadCallback(const int pin);

    /** \fn resetCounter
     * \brief Resets the counter.
     * This function is meant to be used as a trim setting (ie. set it up 
     * where you want it to be)
     */
    void resetCounter() {counterValue = 0;}

private:
    /** \fn updateState
     * \brief Update the new state of the counter
     * This method is thread-safe
     */
    double updateState();

    const int pinA, pinB;
    char state = 0;
    int stateA, stateB;
    std::atomic<int32_t> counterValue;
};

#endif
