#ifndef __STEPPYR_HPP
#define __STEPPYR_HPP

#include "direction.hpp"
#include "drivers/drivers.hpp"
#include "profiles/profiles.hpp"
#include <memory>

class StepperController {
public:
    StepperController(std::shared_ptr<Driver> driver, std::shared_ptr<RampProfile> profile);

    void activate();
    void shutdown();

    void stop();
    void move(long relative_steps);
    void move_to(long absolute_steps);
    void rotate(double degree);

    bool run();

    long next_steps_to_go(long target_steps) const;
    Direction next_direction(long target_steps) const;

    std::shared_ptr<Driver> activator();
    std::shared_ptr<RampProfile> profile();

    /* Proxy methods */

    void step(Direction direction);
    void set_microsteps(int microsteps);

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
    // RPM related helper properties
    long full_steps_per_rev() const;
    void set_full_steps_per_rev(long steps_per_rev);
    void set_target_rpm(double rpm);

    long steps_to_go() const;
    bool is_moving() const;
    Direction direction() const;

private:
    std::shared_ptr<Driver> _driver;
    std::shared_ptr<RampProfile> _profile;

    long calc_degrees_to_steps(double degree) const;
};

#endif
