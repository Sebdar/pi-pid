/** \file constant_value.h
 * \brief Constant value sampler class
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef CONSTANT_VALUE_H
#define CONSTANT_VALUE_H

// Local includes

#include "sampler.h"


/** \class ConstantValue
 * \brief Constant value sampler. Useful for set-point values
 * 
 * The value can be changed by the user on-the-fly.
 */
class ConstantValue : public Sampler {
public:
    // Constructor and destructor
    ConstantValue(double value = 0.0) : cValue(value) {}
    ~ConstantValue() override {}

    // Overridden methods
    int init() override {return 0;}
    int startAcq() override {return 0;}
    int close() override {return 0;}
    double getSample() override {return cValue;}

    // ConstantValue-specific methods
    void setValue(double value) noexcept {cValue = value;}
    double getValue() noexcept {return cValue;}

private:
    double cValue;
};

#endif
