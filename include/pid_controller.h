/** \file pid_controller.h
 * \brief Main PID controller class declaration
 *
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Std includes

#include <thread>
#include <atomic>

// Local includes

#include "controller_interface.h"
#include "sampler.h"
#include "output.h"

struct PidSettings {
    float p;
    float i;
    float d;
};

/** \class PidController
 * \brief Basic 1-dimensional PID Controller
 */
class PidController : public ControllerInterface {
public:
    // Constructor and destructor
    PidController() : settings({0, 0, 0}) {}
    PidController(const PidSettings& _settings) : settings(_settings) {}
    PidController(float p, float i, float d) : settings({p, i, d}) {}

    ~PidController() override {}

    // Overridden methods
    int init() override;
    int startAcq() override;
    int stopAcq() override;
    int startControlLoop() override;
    int stopControlLoop() override;

    // Implementation specific code
    /** \fn setInput
     * \brief The controller will switch to the given input object
     */
    void setInput(Sampler* newSampler) {sampler = newSampler;}

    /** \fn setActuator
     * \brief The controller will switch output to the given output
     */
    void setActuator(Output* newActuator) {actuator = newActuator;}

    /** \fn setSamplingPeriod
     */
    void setSamplingPeriod(std::chrono::nanoseconds ns) {delay = ns;}

    /** \fn setSetPoint
     * \brief Register the target value
     */
    void setSetPoint(double value) {setPoint = value;}

    /** \fn controlLoop
     * \brief Main control loop. Should not be called by the user.
     */
    void controlLoop();

private:
    PidSettings settings;
    Sampler* sampler = nullptr;
    Output* actuator = nullptr;
    double setPoint;

    std::thread* loopThread;
    std::atomic<bool> cont;
    std::chrono::nanoseconds delay = std::chrono::nanoseconds(1000);
};

#endif
