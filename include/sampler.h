/** \file sampler.h
 * \brief Abstract sampler class declaration
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef SAMPLER_H
#define SAMPLER_H

/** \class Sampler
 * \brief The Sampler represents an abstract method of retrieving a value.
 * 
 * The abstraction between the action of "sampling" a value and actually
 * doing it allows us to modify easily how data is obtained (generation,
 * simulation, actual measurements, etc.). An instanciated sampler object is
 * expected from the controllers in this library.
 */
class Sampler {
public:
    // Constructor and destructor
    Sampler() {}
    virtual ~Sampler() {}


    // Sampler functions
    
    /** \fn init
     * \brief Init (or re-init) the sampler object.
     * 
     * This function is expected to be called at the start of the experiment,
     * before starting the acquisitions phadse.
     * Behaviour is dependant on the concrete sampler. This is usually a good
     * moment to launch threads etc.
     */
    virtual int init() = 0;

    /** \fn startAcq
     * \brief Start the continuous data acquisition phase
     * 
     * The sampler should start generating data.
     */
    virtual int startAcq() = 0;

    /** \fn getSample
     * \brief retrieve a sample
     * \throw std::runtime_error if the action could not be executed
     */
    virtual double getSample() = 0;

    /** \fn close
     * \brief Close the sampler. It should not be able to send data afterwards,
     * only after running init again.
     */
    virtual int close() = 0;
    
};

#endif
