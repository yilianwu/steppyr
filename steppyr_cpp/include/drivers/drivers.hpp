#ifndef __STEPPYR_DRIVERS_HPP
#define __STEPPYR_DRIVERS_HPP

#include <math.h>
#include "direction.hpp"

class Driver {
public:
    Driver(int microsteps = 1);
    virtual ~Driver() = 0;

    virtual void activate() = 0;
    virtual void shutdown() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void step(Direction direction) = 0;

    int pulse_width() const;
    void set_pulse_width(int pulse_width_us);

    double max_speed() const;
    void set_max_speed(double max_speed);

    virtual void set_microsteps(int microsteps);

private:
    int _microsteps;
    int _pulse_width_us;
    double _max_speed;
};

#endif