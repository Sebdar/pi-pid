/** \file pid_controller.h
 * \brief Main PID controller class declaration
 *
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Local includes

#include "controller_interface.h"


struct PidSettings {
    float p;
    float i;
    float d;
};

class PidController : public ControllerInterface {
public:
    // Constructor and destructor
    PidController();
    PidController(PidSettings _settings);
    PidController(float p, float i, float d);

    ~PidController() override;

    // Overridden methods
    int init() override;


private:
    PidSettings settings;
};

#endif
