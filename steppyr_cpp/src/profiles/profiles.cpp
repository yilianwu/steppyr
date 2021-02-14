#include <algorithm>
#include "direction.hpp"
#include "utils.h"
#include "profiles/profiles.hpp"
using std::abs;

RampProfile::RampProfile()
    : _current_speed(0.0)
    , _target_speed(1.0) // avoid divide by zero errors
    , _step_interval_us(0)
    , _direction(DIRECTION_CCW)
    , _current_steps(0)
    , _target_steps(0)
    , _previous_target_steps(0)
    , _target_acceleration(1.0) // avoid divide by zero errors
    , _current_acceleration(0.0)
    , _microsteps(1)
    , _full_steps_per_rev(200)
    , _last_step_time_us(0)
    , _next_step_time_us(0)
{}

RampProfile::~RampProfile()
{}

/*
    Property functions
*/


//  Speed
double RampProfile::current_speed() const
{
    return this->_current_speed;
}
double RampProfile::target_speed() const
{
    return this->_target_speed;
}
void RampProfile::set_target_speed(double speed)
{
    if (this->_target_speed == speed) {
        return;
    }
    this->_target_speed = speed;
    this->compute_new_speed();
}

//  Acceleration
double RampProfile::current_acceleration() const
{
    return this->_current_acceleration;
}
double RampProfile::target_acceleration() const
{
    return this->_target_acceleration;
}
void RampProfile::set_target_acceleration(double acceleration)
{
    if (this->_target_acceleration == acceleration) {
        return;
    }
    this->_target_acceleration = acceleration;
    compute_new_speed();
}

// Step
long RampProfile::current_steps() const
{
    return this->_current_steps;
}
void RampProfile::set_current_steps(long position)
{
    this->_target_steps = this->_current_steps = position;
}
void RampProfile::set_target_steps(long absolute_steps)
{
    if (this->_target_steps == absolute_steps) {
        return;
    }
    this->_previous_target_steps = this->_target_steps;
    this->_target_steps = absolute_steps;
    this->compute_new_speed();
}

long RampProfile::microsteps() const
{
    return this->_microsteps;
}
void RampProfile::set_microsteps(long microsteps)
{
    if (this->_microsteps == microsteps) {
        return;
    }
    this->_microsteps = microsteps;
    this->compute_new_speed();
}

// RPM related helper properties
long RampProfile::full_steps_per_rev() const
{
    return this->_full_steps_per_rev;
}
void RampProfile::set_full_steps_per_rev(long steps_per_rev)
{
    this->_full_steps_per_rev = steps_per_rev;
}
void RampProfile::set_target_rpm(double rpm)
{
    this->set_target_speed(calc_speed_from_rpm(rpm));
}

// Other helper properties
long RampProfile::steps_to_go() const
{
    return this->_target_speed - this->_current_speed;
}
bool RampProfile::is_moving() const
{
    return this->steps_to_go() != 0;
}
Direction RampProfile::direction() const
{
    return calc_direction();
}
uint64_t RampProfile::step_interval_us() const
{
    return this->_step_interval_us;
}

/*
    Actions & Derived class Implementation
*/
void RampProfile::stop()
{
    this->_step_interval_us = 0;
    this->_current_speed = 0.0;
}

void RampProfile::step()
{
    if (this->direction() == DIRECTION_CW) {
        this->_current_steps++;
    } else if (this->direction() == DIRECTION_CCW) {
        this->_current_steps--;
    }
    this->compute_new_speed();
    this->_last_step_time_us = timestamp_us();
}
bool RampProfile::should_step()
{
    if (!this->_step_interval_us || !this->steps_to_go()) {
        return false;
    } else {
        return (this->_next_step_time_us && timestamp_us() >= this->_next_step_time_us);
    }
}


inline Direction RampProfile::calc_direction() const
{
    long distanceTo = this->steps_to_go();
    if (distanceTo > 0) {
        return DIRECTION_CW;
    } else if (distanceTo < 0) {
        return DIRECTION_CCW;
    } else {
        return DIRECTION_NONE;
    }
}

inline double calc_step_interval_us(double speed)
{
    if (speed == 0.0) {
        return 0;
    }
    return abs(1000000.0 / speed);
}

double RampProfile::calc_speed_from_rpm(double rpm) const
{
    double rps = rpm / 60.0;
    double microsteps_per_rev = _full_steps_per_rev * _microsteps;
    double speed_steps_per_sec = rps * microsteps_per_rev;
    return speed_steps_per_sec;
}

double calc_speed_from_step_interval(double step_interval_us)
{
    return abs(1000000.0 / step_interval_us);
}
