#ifndef __STEPPYR_PROFILES_ACCEL_HPP
#define __STEPPYR_PROFILES_ACCEL_HPP

#include "profiles/profiles.hpp"

/**
 * Calculates AccelStepper profile.
 * Based on AccelStepper (http://www.airspayce.com/mikem/arduino/AccelStepper).
 **/
class AccelProfile : public RampProfile {
public:
    AccelProfile();
    ~AccelProfile();

    void set_target_speed(double speed) override;

    void set_target_acceleration(double acceleration) override;

    void set_current_steps(long position) override;

    void compute_new_speed() override;

private:
    /** Precomputed sqrt(2 * _acceleration) **/
    double _sqrt_twoa;
    /**
     * Logical step number of current ramp. Not the same as physical step count.
     * 'n' in the Austin paper
     * Used for calculating acceleration and deceleration.
     * When +ve, we are accelerating; when -ve, we are decelerating.
     **/
    long _ramp_step_number;
    /**
     * _timer_count is 'c' in Austin paper
     * Defaults to 1.0 to avoid divide by zero errors
     **/
    double _ramp_delay_0_us;
    /**
     * All timer counts > _ramp_delay_0_us. _timer_count is 'c' in Austin paper
     * Defaults to 1.0 to avoid divide by zero errors
     **/
    double _ramp_delay_n_us;
    /** Minimum microseconds for ramp delay **/
    double _ramp_delay_min_us;

    /**
     * Recompute ramp step number from current speed and adjust speed if accelerating or cruising
     *
     * Equation 16
     **/
    long calc_ramp_step_number_16() const;

    /**
     * Recompute _ramp_step_number per Equation 17
     **/
    long calc_ramp_step_number_17(double new_acceleration) const;

    /**
     * New c0 per Equation 7, with correction per Equation 15
     **/
    double calc_ramp_delay_0(double acceleration) const;

    /**
     * Equation 13
     **/
    double calc_ramp_delay_n() const;
};

#endif