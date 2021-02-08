#include "steppyr.hpp"
using std::shared_ptr;

StepperController::StepperController(shared_ptr<Driver> driver, shared_ptr<RampProfile> profile)
    : _driver(driver), _profile(profile)
{}

void StepperController::activate()
{
    this->_driver->activate();
}

void StepperController::shutdown()
{
    this->_driver->shutdown();
}

void StepperController::stop()
{
    this->_profile->stop();
}

void StepperController::move(long relative_steps)
{
    this->move_to(this->_profile->current_steps() + relative_steps);
}

void StepperController::move_to(long absolute_steps)
{
    this->set_target_steps(absolute_steps);
}

void StepperController::rotate(double degree)
{
    this->move(calc_degrees_to_steps(degree));
}

bool StepperController::run()
{
    if (this->_profile->should_step()) {
        this->_driver->step(this->_profile->direction());
        this->_profile->step();
    }
    return this->_profile->is_moving();
}

long StepperController::next_steps_to_go(long target_steps) const
{
    return target_steps - this->_profile->current_steps();
}

Direction StepperController::next_direction(long target_steps) const
{
    if (this->next_steps_to_go(target_steps) > 0) {
        return DIRECTION_CW;
    } else {
        return DIRECTION_CCW;
    }
}

std::shared_ptr<Driver> StepperController::activator()
{
    return this->_driver;
}

std::shared_ptr<RampProfile> StepperController::profile()
{
    return this->_profile;
}

void StepperController::step(Direction direction)
{
    this->_driver->step(direction);
}

void StepperController::set_microsteps(int microsteps)
{
    this->_driver->set_microsteps(microsteps);
    this->_profile->set_microsteps(microsteps);
}

double StepperController::current_speed() const
{
    return this->_profile->current_speed();
}
double StepperController::target_speed() const
{
    return this->_profile->target_speed();
}
void StepperController::set_target_speed(double speed)
{
    this->_profile->set_target_speed(speed);
}

double StepperController::current_acceleration() const
{
    return this->_profile->current_acceleration();
}
double StepperController::target_acceleration() const
{
    return this->_profile->target_acceleration();
}
void StepperController::set_target_acceleration(double acceleration)
{
    this->_profile->set_target_acceleration(acceleration);
}

long StepperController::current_steps() const
{
    return this->_profile->current_steps();
}
void StepperController::set_current_steps(long position)
{
    this->_profile->set_current_steps(position);
}
void StepperController::set_target_steps(long absolute_steps)
{
    this->_profile->set_target_steps(absolute_steps);
}

long StepperController::full_steps_per_rev() const
{
    return this->_profile->full_steps_per_rev();
}
void StepperController::set_full_steps_per_rev(long steps_per_rev)
{
    this->_profile->set_full_steps_per_rev(steps_per_rev);
}
void StepperController::set_target_rpm(double rpm)
{
    this->_profile->set_target_rpm(rpm);
}

long StepperController::steps_to_go() const
{
    return this->_profile->steps_to_go();
}
bool StepperController::is_moving() const
{
    return this->_profile->is_moving();
}
Direction StepperController::direction() const
{
    return this->_profile->direction();
}


long StepperController::calc_degrees_to_steps(double degree) const
{
    return (long)(degree * this->_profile->full_steps_per_rev() * this->_profile->microsteps() / 360.0);
}