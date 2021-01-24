/** \file firstorder.h
 * \brief First Order system simulation declaration
 *
 * \details Implements a first-order system for use within a simulation. This
 * system implements both a sampler and an output.
 *
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */


#ifndef FIRSTORDER_H
#define FIRSTORDER_H

// Local includes

#include "sampler.h"
#include "output.h"


/** \class FirstOrder
 * \brief The first order class defines a simulated system which acts like an
 * infinite mean with exponential decay.
 *
 * \details This system is described as : $y[n] = x[n] + \alpha y[n-1]$.
 *
 * It might be confusing to use "setOutput" as an input for the system, but it
 * is the simplest way to adapt Sampler and Output for a simulation.
 * setOutput -> the output of the controller <=> input of the system
 * getSample -> input of the controller <=> output of the system
 *
 * Beware, calling getSample is equivalent to calculating a new value
 */
class FirstOrder : public Sampler, public Output {
public:
    // Constructor and destructor
    FirstOrder() = default;
    FirstOrder(double decay) 
        : alpha(decay) {}
    ~FirstOrder() = default;

    // Reimplemented functions
    int init() override {return 0;}
    int startAcq() override {last = 0.; return 0;}
    int setOutput(const double val) override {x = val; return 0;}
    double getCurrentOutput() override {return x;}
    double getSample() override {last = (1.0 - alpha) * x + alpha*last; return last;}
    int close() override {return 0;}

private:
    double last = 0.; // last value (y[n-1])
    double alpha = 0.5; // Decay rate
    double x = 0.; // input
};

#endif

