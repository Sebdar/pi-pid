/** \file incremental_encoder.cpp
 * \brief Incremental encoder testing tool
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

// Std includes

#include <iostream>

// Local includes

#include <encoder_counter.h>


int main() {
    EncoderCounter counter(17, 27);
    counter.init();
    counter.startAcq();
    
    int dummy;
    std::cin >> dummy;
    
    return 0;
}