/** \file controller_interface.h
 * \brief Abstract controller interface for inheritance
 * 
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H

/** \class ControllerInterface
 * \brief Abstract Controller interface. This class defines how controllers
 * should interact with the user interface.
 */
class ControllerInterface {
public:
    // Constructor and destructor
    ControllerInterface() {};
    virtual ~ControllerInterface() {};
    
    // Controller actions

    /** \fn init
     * \brief Init (or re-init) the controller.
     * 
     * This function is expected to be called at the start of the experiment,
     * before starting the acquisitions phase. This will trigger an init to all
     * samplers & output handlers.
     */
    virtual int init() = 0;

    /** \fn startAcq
     * \brief Start the continuous data acquisition phase
     * 
     * This does not generate any output - the controller should remain
     * inactive.
     */
    virtual int startAcq() = 0;

    /** \fn stopAcq
     * \brief Stop the samplers
     */
    virtual int stopAcq() = 0;

    /** \fn startControlLoop
     * \brief Start controlling the output based on the current input values
     * The "heart" of the controller. This should return directly, while the
     * control loop is executed in a separate thread.
     */
    virtual int startControlLoop() = 0;

    /** \fn stopControlLoop
     * \brief Stops the PID Controller. Actuators will be stopped
     */
    virtual int stopControlLoop() = 0;
};

#endif
