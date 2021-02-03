#ifndef __STEPPYR_PROFILES_HPP
#define __STEPPYR_PROFILES_HPP

#include <inttypes.h>
#include "direction.hpp"

class RampProfile {
protected:
    RampProfile();
public:
    virtual ~RampProfile() = 0;

    /*
        Property functions
    */
    // Speed
    double current_speed() const;
    double target_speed() const;
    void set_target_speed(double speed);

    // Acceleration
    double current_acceleration() const;
    double target_acceleration() const;
    void set_target_acceleration(double acceleration);

    // Step
    long current_steps() const;
    void set_current_steps(long position);
    void set_target_steps(long absolute_steps);

    long microsteps() const;
    void set_microsteps(long microsteps);

    // RPM related helper properties
    long full_steps_per_rev() const;
    void set_full_steps_per_rev(long steps_per_rev);
    void set_target_rpm(double rpm);

    // Other helper properties
    long steps_to_go() const;
    bool is_moving() const;
    Direction direction() const;
    uint64_t step_interval_us() const;

    /*
        Actions & Derived class Implementation
    */
    virtual void stop();

    virtual void step();
    virtual bool should_step();
    virtual void compute_new_speed() = 0;

protected:
    double _current_speed;
    double _target_speed;
    long _step_interval_us;
    Direction _direction;
    long _current_steps;
    long _target_steps;
    long _previous_target_steps;
    double _target_acceleration;
    double _current_acceleration;
    long _microsteps;
    long _full_steps_per_rev;
    uint64_t _last_step_time_us;
    uint64_t _next_step_time_us;

private:
    Direction calc_direction() const;
    double calc_step_interval_us() const;
    double calc_speed_from_rpm(double full_steps_per_rev) const;
    double calc_speed_from_step_interval() const;
};

#endif
