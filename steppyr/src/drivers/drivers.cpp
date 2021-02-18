#include <pybind11/pybind11.h>
#include <drivers/drivers.hpp>
#include "modules.h"
namespace py = pybind11;

class PyDriver: public Driver {
public:
    PyDriver(int microsteps = 1)
        : Driver(microsteps)
    {}
    ~PyDriver() {}

    void activate() override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            Driver,
            activate
        );
    }

    void shutdown() override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            Driver,
            shutdown
        );
    }

    void enable() override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            Driver,
            enable
        );
    }

    void disable() override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            Driver,
            disable
        );
    }

    void step(Direction direction) override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE_PURE(
            void,
            Driver,
            step,
            direction
        );
    }

    void set_microsteps(int microsteps) override {
        py::gil_scoped_acquire acquire;

        PYBIND11_OVERRIDE(
            void,
            Driver,
            set_microsteps,
            microsteps
        );
    }
};

void module_def_drivers(py::module_ &m)
{
    py::class_<Driver, PyDriver, std::shared_ptr<Driver>>(m, "Driver")
        .def(py::init<>())
        .def(py::init<int>())
        .def("activate", &Driver::activate)
        .def("shutdown", &Driver::shutdown)
        .def("enable", &Driver::enable)
        .def("disable", &Driver::disable)
        .def("step", &Driver::step)
        .def_property_readonly("pulse_width", &Driver::pulse_width)
        .def("set_pulse_width", &Driver::set_pulse_width)
        .def_property_readonly("max_speed", &Driver::max_speed)
        .def("set_max_speed", &Driver::set_max_speed)
        .def("set_microsteps", &Driver::set_microsteps)
    ;

    py::module_ m_stepdir = m.def_submodule("stepdir");
    module_def_stepdir(m_stepdir);
}
