#include "drivers/drivers.hpp"

Driver::Driver(int microsteps)
    : _pulse_width_us(2), _microsteps(microsteps), _max_speed(INFINITY)
{}

Driver::~Driver()
{}

int Driver::pulse_width() const
{
    return this->_pulse_width_us;
}
void Driver::set_pulse_width(int pulse_width_us)
{
    this->_pulse_width_us = pulse_width_us;
}

double Driver::max_speed() const
{
    return this->_max_speed;
}
void Driver::set_max_speed(double max_speed)
{
    this->_max_speed = max_speed;
}

void Driver::set_microsteps(int microsteps)
{
    this->_microsteps = microsteps;
}