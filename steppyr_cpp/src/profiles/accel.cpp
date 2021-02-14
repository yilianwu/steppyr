#include "profiles/accel.hpp"
#include "utils.h"
#include <algorithm>
#include <math.h>
using std::max;

AccelProfile::AccelProfile()
    : RampProfile()
    , _sqrt_twoa(1.0)
    , _ramp_step_number(0)
    , _ramp_delay_0_us(1.0)
    , _ramp_delay_n_us(1.0)
    , _ramp_delay_min_us(1.0)
{
}

AccelProfile::~AccelProfile()
{}

void AccelProfile::set_target_speed(double speed)
{
    if (this->_target_speed == speed) {
        return;
    }
    this->_target_speed = speed;

    this->_ramp_delay_min_us = 1000000.0 / speed;
    if (this->_ramp_step_number > 0) {
        this->_ramp_step_number = calc_ramp_step_number_16();
        this->compute_new_speed();
    }
}

void AccelProfile::set_target_acceleration(double acceleration)
{
    if (acceleration == 0.0 || this->_target_acceleration == acceleration) {
        return;
    }
    this->_ramp_step_number = calc_ramp_step_number_17(acceleration);
    this->_ramp_delay_0_us = calc_ramp_delay_0(acceleration);
    this->_target_acceleration = acceleration;
    this->_current_acceleration = acceleration;
    this->compute_new_speed();
}

void AccelProfile::compute_new_speed()
{
    // Save distance to go
    long distanceTo = this->steps_to_go();
    // stepsToStop = int(((self._current_speed * self._current_speed) / (2.0 * self._target_acceleration))) # Equation 16
    // Get number of steps until stop per Equation 16
    long stepsToStop = calc_ramp_step_number_16();

    if (distanceTo == 0 && stepsToStop <= 1) {
        // We are at the target and its time to stop
        this->stop();
        this->set_current_steps(0);
        return;
    }

    if (distanceTo > 0) {
        // We are anticlockwise from the target
        // Need to go clockwise from here, maybe decelerate now
        if (_ramp_step_number > 0) {
            // Currently accelerating, need to decel now? Or maybe going the wrong way?
            if ((stepsToStop >= distanceTo) || (_direction == DIRECTION_CCW)) {
                // Start deceleration
                _ramp_step_number = -stepsToStop;
            }
        } else if (_ramp_step_number < 0) {
            // Currently decelerating, need to accel again?
            if ((stepsToStop < distanceTo) && (_direction == DIRECTION_CW)) {
                // Start acceleration
                _ramp_step_number = -_ramp_step_number;
            }
        }
    } else if (distanceTo < 0) {
        // We are clockwise from the target
        // Need to go anticlockwise from here, maybe decelerate
        if (_ramp_step_number > 0) {
            // Currently accelerating, need to decel now? Or maybe going the wrong way?
            if ((stepsToStop >= -distanceTo) || (_direction == DIRECTION_CW)) {
                // Start deceleration
                _ramp_step_number = -stepsToStop;
            }
        } else if (_ramp_step_number < 0) {
            // Currently decelerating, need to accel again?
            if ((stepsToStop < -distanceTo) && (_direction == DIRECTION_CCW)) {
                // Start acceleration
                _ramp_step_number = -_ramp_step_number;
            }
        }
    }

    // Need to accelerate or decelerate
    if (_ramp_step_number == 0) {
        // First step from stopped
        _ramp_delay_n_us = _ramp_delay_0_us;
        _direction = direction();
    } else {
        // Subsequent step. Works for accel (_ramp_step_number is +_ve) and decel (_ramp_step_number is -ve).
        double ramp_delay_n_us = calc_ramp_delay_n();
        _ramp_delay_n_us = max(ramp_delay_n_us, _ramp_delay_min_us);
    }

    _ramp_step_number++;
    _step_interval_us = _ramp_delay_n_us;
    _next_step_time_us = timestamp_us() + _step_interval_us;
    _current_speed = calc_speed_from_step_interval(_ramp_delay_n_us);
}

void AccelProfile::set_current_steps(long position)
{
    RampProfile::set_current_steps(position);
    this->_ramp_step_number = 0;
}


inline long AccelProfile::calc_ramp_step_number_16() const
{
    return (long)((_current_speed * _current_speed) / (2.0 * _current_acceleration));
}

inline long AccelProfile::calc_ramp_step_number_17(double new_acceleration) const
{
    return (long)(_ramp_step_number * (_current_acceleration / new_acceleration));
}

inline double AccelProfile::calc_ramp_delay_0(double acceleration) const
{
    return 0.676 * sqrt(2.0 / acceleration) * 1000000.0;
}

inline double AccelProfile::calc_ramp_delay_n() const
{
    return _ramp_delay_n_us - ((2.0 * _ramp_delay_n_us) / ((4.0 * _ramp_step_number) + 1));
}
