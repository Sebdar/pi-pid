/** \file pid_controller.h
 * \brief Main PID controller class declaration
 *
 * \author Sebastien Darche <sebastien.darche@free.fr>
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <controller_interface.h>

class PidController : public ControllerInterface {
public:
    PidController();
    ~PidController() override;

    int init() override;
};

#endif
