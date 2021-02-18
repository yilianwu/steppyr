#include "drivers/stepdir.hpp"
#include <pigpio.h>
#include <unistd.h>

StepDirDriver::StepDirDriver(int dir_pin, int step_pin, int enable_pin)
    : Driver(), dir_pin(dir_pin), step_pin(step_pin), enable_pin(enable_pin)
{
    gpioInitialise();
}

StepDirDriver::~StepDirDriver()
{
}

void StepDirDriver::activate()
{
    gpioSetMode(this->dir_pin, PI_OUTPUT);
    gpioWrite(this->dir_pin, 1);
    gpioSetMode(this->step_pin, PI_OUTPUT);
    gpioWrite(this->step_pin, 0);
    this->enable();
}

void StepDirDriver::shutdown()
{
    this->shutdown();
}

void StepDirDriver::enable()
{
    if (this->enable_pin > 0) {
        gpioSetMode(this->enable_pin, PI_OUTPUT);
        gpioWrite(this->enable_pin, 0);
    }
}

void StepDirDriver::disable()
{
    if (this->enable_pin > 0) {
        gpioSetMode(this->enable_pin, PI_OUTPUT);
        gpioWrite(this->enable_pin, 1);
    }
}

void StepDirDriver::step(Direction direction)
{
    // Set direction first else get rogue pulses
    gpioWrite(this->dir_pin, (direction == DIRECTION_CCW ? 0 : 1));
    gpioWrite(this->step_pin, 1);
    // Caution 200ns setup time
    // Delay the minimum allowed pulse width
    usleep(this->_pulse_width_us);
    gpioWrite(this->step_pin, 0);
}
