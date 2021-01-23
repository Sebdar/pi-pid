/** \file sine.cpp
 * \brief Sine wave generator definition
 *
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <cmath>

// Local includes

#include "samplers/sine.h"

double Sine::Pi = std::cos(static_cast<double>(0));


int Sine::startAcq() {
    t0 = std::chrono::steady_clock::now();
    return 0;
}

double Sine::getSample() {
    auto now = std::chrono::steady_clock::now();

    // Using microseconds resolution : this *should* be enough
    auto ticks = 
        std::chrono::duration_cast<std::chrono::microseconds>(now - t0).count();
    double t = static_cast<double>(ticks) / 1.e6; // Converting to seconds

    return std::sin(2*Pi*t + p);
}

