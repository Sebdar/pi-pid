/** \file sine.h
 * \brief Sine wave generator declaration
 *
 * \author Sebastien Darche <sebastien.darche@fre.fr>
 */

#ifndef SINE_H
#define SINE_H


// Std includes

#include <chrono>

// Local includes

#include "sampler.h"


/** \class Sine
 * \brief Basic sine wave generator sampler
 */
class Sine : public Sampler {
public:
    // Constructor & destructor
    /** default ctor
     * \brief Basic sine wave. Default frequency is 1 Hz, without phase
     */
    Sine() = default;
    
    Sine(double frequency, double phase);

    virtual ~Sine() = default;

    // Sampler functions
    int init() override {return 0;}
    int startAcq() override;
    int close() override {return 0;}
    double getSample() override;

    // Sine-specific methods
    /** \fn setFrequency
     * \brief Set frequency to the given value (in Hz)
     */
    void setFrequency(double freq) {f = freq;}
    
    /** \fn setPhase
     * \brief Set the phase shift to the given value (in rad)
     */
    void setPhase(double phi) {p = phi;}
    
    /** \brief a handy Pi value without polluting your namespace ;)
    */
    static double Pi;
private:
    double f{2*Pi};
    double p{0};
    
    std::chrono::time_point<std::chrono::steady_clock> t0;
};


#endif // SINE_H

