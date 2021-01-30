#ifndef __STEPPYR_DRIVER_HPP
#define __STEPPYR_DRIVER_HPP

#include <math.h>

class Driver {
public:
    Driver(int microsteps = 1)
        : _pulse_width_us(2), _microsteps(microsteps), _max_speed(INFINITY)
    {}
    virtual ~Driver() {}

    virtual void activate() {}
    virtual void shutdown() {}
    virtual void enable() {}
    virtual void disable() {}
    virtual void step(int direction) {}

    int pulse_width() const
    {
        return this->_pulse_width_us;
    }
    void set_pulse_width(int pulse_width_us)
    {
        this->_pulse_width_us = pulse_width_us;
    }

    double max_speed() const
    {
        return this->_max_speed;
    }
    void set_max_speed(double max_speed)
    {
        this->_max_speed = max_speed;
    }

    virtual void set_microsteps(int microsteps)
    {
        this->_microsteps = microsteps;
    }

private:
    int _microsteps;
    int _pulse_width_us;
    double _max_speed;
};

#endif