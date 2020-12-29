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
    void setInput(Sampler* newSampler) noexcept {sampler = newSampler;}

    /** \fn setReference
     * \brief Register the reference value (set-point)
     */
    void setReference(Sampler* newReference) noexcept {reference = newReference;}

    /** \fn setActuator
     * \brief The controller will switch output to the given output
     */
    void setActuator(Output* newActuator) noexcept {actuator = newActuator;}

    /** \fn setSamplingPeriod
     */
    void setSamplingPeriod(std::chrono::microseconds us) noexcept {delay = us;}

    /** \fn controlLoop
     * \brief Main control loop. Should not be called by the user!
     */
    void controlLoop();

    // ---- PID Tuning ---- //

    /** \fn setPidP
     * \fn setPidI
     * \fn setPidP
     * \brief Adjust the corresponding coefficents
     */
    void setPidP(float _p) noexcept {settings.p = _p;}
    void setPidI(float _i) noexcept {settings.i = _i;}
    void setPidD(float _d) noexcept {settings.d = _d;}

    /** \fn setDerivativeDecay
     * \brief Adjusts the decay rate on the derivative low-pass filter
     * \details a decay rate of 1 disables the filter (not recommended!)
     */
    void setDerivativeDecay(double _d) noexcept {decay = _d;}

    /** \fn setIntegratorBounds
     * \brief Limits how much the integrator can accumulate errors over time
     */
    void setIntegratorBounds(double lower, double upper) noexcept;
    
private:
    PidSettings settings;
    Sampler* sampler = nullptr;
    Sampler* reference = nullptr;
    Output* actuator = nullptr;

    // -- Thread handling --  //

    std::thread* loopThread;
    std::atomic<bool> cont;
    std::chrono::microseconds delay = std::chrono::microseconds(10000);

    // ---- PID Settings ---- //

    /** \brief decay on the derivative computation
     * \see setDerivativeDecay
     */
    double decay = 0.5;

    /** \brief lower and upper bounds on the integrator
     * \see setIntegratorBounds
     */
    double integratorLower = std::numeric_limits<double>::min();
    double integratorUpper = std::numeric_limits<double>::max();

    // ---- PID Values ---- //
    // For plotting & logging utilities
    double sample, setPoint, y, out;
};

#endif
