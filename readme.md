# PiPid - A C++-based graphical PID Controller for the raspberry pi
## Sébastien Darche

## Abstract

The PiPid project is a C++ framework / GUI app to control physical processes. As this is a
personnal project, it is more focused for a specific usage (video coming as soon as it is
working ;) ).


## Requirements & Installation

This project requires :

- A Raspberry Pi (duh)
- WiringPi library (installed by default)
- Qt 5
- A system you have to control (duh²)
 

To instal the project, run the `bootstrap.sh` script from the cloned repo, then cd into build
and run `make`.

## Hardware-specific implementation

PiPid comes with a substantial amount of abstraction, allowing it to work on many devices.

### Samplers

Samplers represent the inputs of the system. This layer of abstraction allows the developper to adapt them to their specific application : sensors, simulated values, etc. Simply inherit the master class `sampler`.

As an example, the `EncoderCounter` represents an interface for a circular relative incremental encoder (IVO G314 - but this can probably be used with another coding wheel).

### Outputs

An `Output` object represents a controllable quantity that can be controlled. The example is a PWM-based ESC motor driver (similar to a servomotor).

### Controller

The hearth of this library. For now, only a "basic" 1-dimensional PID is implemented.

## Using PiPid

- Develop your own sampler & output for your system
- Connect them to the PID (see `test/simple_pid.cpp` for an example)

PLEASE exercise caution with your system, a bad configuration of the PID may cause damages to your system depending on what you're controlling (a high-speed propeller in my case, which could possibly cut off a finger). Do not hold me responsible for any harm / damages caused by PiPid!

## Tools

A few small python tools are located in `tools` for a quick check-up of I/O devices. It is encouraged to try testing your output before hooking them up to the PID, first with a simple script then through a unit test of your C++ Class ;).
