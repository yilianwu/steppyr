#include "steppyr.hpp"
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <unistd.h>
using std::shared_ptr, std::scoped_lock;
using std::memory_order_acquire, std::memory_order_acq_rel, std::memory_order_relaxed;

void stepper_thread_main(StepperController &stepper)
{
    while (stepper.thread_running.load(memory_order_acquire)) {
        stepper.run();
        usleep(stepper.poll_us.load(memory_order_relaxed));
    }
}

StepperController::StepperController(shared_ptr<Driver> driver, shared_ptr<RampProfile> profile)
    : _driver(driver), _profile(profile), thread_running(false), poll_us(50)
{}

StepperController::~StepperController()
{
    this->terminate();
}

void StepperController::activate()
{
    // Lock the related mutex when access
    scoped_lock lock(this->driver_lock);

    this->_driver->activate();
}

void StepperController::shutdown()
{
    scoped_lock lock(this->driver_lock);

    this->_driver->shutdown();
}

void StepperController::stop()
{
    scoped_lock lock(this->profile_lock);

    this->_profile->stop();
}

void StepperController::move(long relative_steps)
{
    long step_to;
    {
        scoped_lock lock(this->profile_lock);
        step_to = this->_profile->current_steps() + relative_steps;
    }

    this->move_to(step_to);
}

void StepperController::move_to(long absolute_steps)
{
    this->set_target_steps(absolute_steps);
}

void StepperController::rotate(double degree)
{
    long step_to;
    {
        scoped_lock lock(this->profile_lock);
        step_to = this->_profile->current_steps();
        step_to += calc_degrees_to_steps(
            this->_profile->full_steps_per_rev(),
            this->_profile->microsteps(),
            degree);
    }

    this->move_to(step_to);
}

bool StepperController::run()
{
    scoped_lock lock(this->driver_lock, this->profile_lock);

    if (this->_profile->should_step()) {
        this->_driver->step(this->_profile->direction());
        this->_profile->step();
    }
    return this->_profile->is_moving();
}

void StepperController::spawn()
{
    bool spawned = this->thread_running.exchange(true, memory_order_acq_rel);
    if (spawned || this->stepper_thread.joinable()) {
        return;
    }
    this->stepper_thread = std::thread(stepper_thread_main, std::ref(*this));
}

void StepperController::terminate()
{
    bool spawned = this->thread_running.exchange(false, memory_order_acq_rel);
    if (!spawned || !this->stepper_thread.joinable()) {
        return;
    }
    this->stepper_thread.join();
    this->stepper_thread = std::thread();
}

bool StepperController::is_spawned() const
{
    return this->thread_running.load(memory_order_acquire);
}

unsigned StepperController::thread_poll_us() const
{
    return this->poll_us.load(memory_order_relaxed);
}

void StepperController::set_thread_poll_us(unsigned us)
{
    this->poll_us.store(us, memory_order_relaxed);
}

long StepperController::next_steps_to_go(long target_steps) const
{
    scoped_lock lock(this->profile_lock);

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

/*
std::shared_ptr<Driver> StepperController::activator()
{
    return this->_driver;
}

std::shared_ptr<RampProfile> StepperController::profile()
{
    return this->_profile;
}
*/

void StepperController::step(Direction direction)
{
    scoped_lock lock(this->driver_lock);

    this->_driver->step(direction);
}

void StepperController::set_microsteps(int microsteps)
{
    scoped_lock lock(this->driver_lock, this->profile_lock);

    this->_driver->set_microsteps(microsteps);
    this->_profile->set_microsteps(microsteps);
}

double StepperController::current_speed() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->current_speed();
}
double StepperController::target_speed() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->target_speed();
}
void StepperController::set_target_speed(double speed)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_target_speed(speed);
}

double StepperController::current_acceleration() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->current_acceleration();
}
double StepperController::target_acceleration() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->target_acceleration();
}
void StepperController::set_target_acceleration(double acceleration)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_target_acceleration(acceleration);
}

long StepperController::current_steps() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->current_steps();
}
void StepperController::set_current_steps(long position)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_current_steps(position);
}
void StepperController::set_target_steps(long absolute_steps)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_target_steps(absolute_steps);
}

long StepperController::full_steps_per_rev() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->full_steps_per_rev();
}
void StepperController::set_full_steps_per_rev(long steps_per_rev)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_full_steps_per_rev(steps_per_rev);
}
void StepperController::set_target_rpm(double rpm)
{
    scoped_lock lock(this->profile_lock);

    this->_profile->set_target_rpm(rpm);
}

long StepperController::steps_to_go() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->steps_to_go();
}
bool StepperController::is_moving() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->is_moving();
}
Direction StepperController::direction() const
{
    scoped_lock lock(this->profile_lock);

    return this->_profile->direction();
}


long calc_degrees_to_steps(double full_steps_per_rev, double microsteps, double degree)
{
    return (long)(degree * full_steps_per_rev * microsteps / 360.0);
}