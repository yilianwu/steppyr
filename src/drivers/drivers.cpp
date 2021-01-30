#include "drivers/drivers.hpp"
#include <boost/python.hpp>

using namespace boost::python;

struct Driver_Wrapper: Driver, wrapper<Driver> {
    Driver_Wrapper(int microsteps = 1)
        : Driver(microsteps)
    {}

    void activate()
    {
        if (override f = this->get_override("activate")) {
            f();
            return;
        }
        return Driver::activate();
    }
    void activate_def()
    {
        return this->Driver::activate();
    }

    void shutdown()
    {
        if (override f = this->get_override("shutdown")) {
            f();
            return;
        }
        return Driver::shutdown();
    }
    void shutdown_def()
    {
        return this->Driver::shutdown();
    }

    void enable()
    {
        if (override f = this->get_override("enable")) {
            f();
            return;
        }
        return Driver::enable();
    }
    void enable_def()
    {
        return this->Driver::enable();
    }

    void disable()
    {
        if (override f = this->get_override("disable")) {
            f();
            return;
        }
        return Driver::disable();
    }
    void disable_def()
    {
        return this->Driver::disable();
    }

    void step(int direction)
    {
        if (override f = this->get_override("step")) {
            f(direction);
            return;
        }
        return Driver::step(direction);
    }
    void step_def(int direction)
    {
        return this->Driver::step(direction);
    }

    void set_microsteps(int microsteps)
    {
        if (override f = this->get_override("set_microsteps")) {
            f(microsteps);
            return;
        }
        return Driver::set_microsteps(microsteps);
    }
    void set_microsteps_def(int microsteps)
    {
        return this->Driver::set_microsteps(microsteps);
    }
};

BOOST_PYTHON_MODULE(drivers)
{
    class_<Driver_Wrapper, boost::noncopyable>("Driver")
        .def(init<optional<int>>())
        .def("activate", &Driver::activate, &Driver_Wrapper::activate_def)
        .def("shutdown", &Driver::shutdown, &Driver_Wrapper::shutdown_def)
        .def("enable", &Driver::enable, &Driver_Wrapper::enable_def)
        .def("disable", &Driver::disable, &Driver_Wrapper::disable_def)
        .def("step", &Driver::step, &Driver_Wrapper::step_def)
        .add_property("pulse_width", &Driver::pulse_width, &Driver::set_pulse_width)
        .add_property("max_speed", &Driver::max_speed, &Driver::set_max_speed)
        .def("set_microsteps", &Driver::set_microsteps, &Driver_Wrapper::set_microsteps_def)
    ;
}
