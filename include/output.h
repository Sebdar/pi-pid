/** \file output.h
 * \brief Output abstract interface
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef OUTPUT_H
#define OUTPUT_H

class Output {
public:
    // Constructor and destructor
    Output() {}
    virtual ~Output() {}

    // Output specific controls
    /** \fn init
     * \brief Initialize the output actuator
     */
    virtual int init() = 0;
    
    /** \fn setOutput
     * \brief Outputs the given value (implementation specific)
     */
    virtual int setOutput(const double output) = 0;

    /** \fn getCurrentOutput
     * \brief Returns the current applied output
     */
    virtual double getCurrentOutput() = 0;

    /** \fn close
     * \brief Stops the output handler (implementation specific)
     */
    virtual int close() = 0;

};

#endif
