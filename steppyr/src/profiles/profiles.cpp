#include <pybind11/pybind11.h>
#include <profiles/profiles.hpp>
#include "modules.h"
namespace py = pybind11;

class PyProfile : public RampProfile {
public:
    PyProfile()
        : RampProfile()
    {}
    ~PyProfile() {}

    void set_target_speed(double speed) override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            set_target_speed,
            speed
        );
    }

    void set_target_acceleration(double acceleration) override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            set_target_acceleration,
            acceleration
        );
    }

    void set_current_steps(long position) override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            set_current_steps,
            position
        );
    }

    void set_target_steps(long absolute_steps) override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            set_target_steps,
            absolute_steps
        );
    }

    void set_microsteps(long microsteps) override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            set_microsteps,
            microsteps
        );
    }

    void stop() override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            stop
        );
    }

    void step() override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            RampProfile,
            step
        );
    }

    bool should_step() override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            bool,
            RampProfile,
            should_step
        );
    }

    void compute_new_speed() override
    {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            RampProfile,
            compute_new_speed
        );
    }
};

void module_def_profiles(py::module_ &m)
{
    py::class_<RampProfile, PyProfile>(m, "RampProfile")
        .def(py::init<>())
        .def("current_speed", &RampProfile::current_speed)
        .def("target_speed", &RampProfile::target_speed)
        .def("set_target_speed", &RampProfile::set_target_speed)
        .def("current_acceleration", &RampProfile::current_acceleration)
        .def("target_acceleration", &RampProfile::target_acceleration)
        .def("set_target_acceleration", &RampProfile::set_target_acceleration)
        .def("current_steps", &RampProfile::current_steps)
        .def("set_current_steps", &RampProfile::set_current_steps)
        .def("set_target_steps", &RampProfile::set_target_steps)
        .def("microsteps", &RampProfile::microsteps)
        .def("set_microsteps", &RampProfile::set_microsteps)
        .def("full_steps_per_rev", &RampProfile::full_steps_per_rev)
        .def("set_full_steps_per_rev", &RampProfile::set_full_steps_per_rev)
        .def("set_target_rpm", &RampProfile::set_target_rpm)
        .def("steps_to_go", &RampProfile::steps_to_go)
        .def("is_moving", &RampProfile::is_moving)
        .def("direction", &RampProfile::direction)
        .def("step_interval_us", &RampProfile::step_interval_us)
        .def("stop", &RampProfile::stop)
        .def("step", &RampProfile::step)
        .def("should_step", &RampProfile::should_step)
        .def("compute_new_speed", &RampProfile::compute_new_speed)
    ;

    py::module_ m_accel = m.def_submodule("accel");
    module_def_accel(m_accel);
}
