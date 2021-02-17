#include <pybind11/pybind11.h>
#include "steppyr.hpp"
using std::shared_ptr;
namespace py = pybind11;

PYBIND11_MODULE(steppyr, m) {
    py::class_<StepperController>(m, "StepperController")
        .def(py::init<shared_ptr<Driver>, shared_ptr<RampProfile>>())
        .def("activate", &StepperController::activate)
        .def("shutdown", &StepperController::shutdown)
        .def("stop", &StepperController::stop)
        .def("move", &StepperController::move)
        .def("move_to", &StepperController::move_to)
        .def("rotate", &StepperController::rotate)
        .def("run", &StepperController::run)
        .def("spawn", &StepperController::spawn, py::call_guard<py::gil_scoped_release>())
        .def("terminate", &StepperController::terminate)
        .def("is_spawned", &StepperController::is_spawned)
        .def("next_steps_to_go", &StepperController::next_steps_to_go)
        .def("next_direction", &StepperController::next_direction)
        .def("step", &StepperController::step)
        .def("set_microsteps", &StepperController::set_microsteps)
        .def("current_speed", &StepperController::current_speed)
        .def("target_speed", &StepperController::target_speed)
        .def("set_target_speed", &StepperController::set_target_speed)
        .def("current_acceleration", &StepperController::current_acceleration)
        .def("target_acceleration", &StepperController::target_acceleration)
        .def("set_target_acceleration", &StepperController::set_target_acceleration)
        .def("current_steps", &StepperController::current_steps)
        .def("set_current_steps", &StepperController::set_current_steps)
        .def("set_target_steps", &StepperController::set_target_steps)
        .def("full_steps_per_rev", &StepperController::full_steps_per_rev)
        .def("set_full_steps_per_rev", &StepperController::set_full_steps_per_rev)
        .def("set_target_rpm", &StepperController::set_target_rpm)
        .def("steps_to_go", &StepperController::steps_to_go)
        .def("is_moving", &StepperController::is_moving)
        .def("direction", &StepperController::direction)
    ;
}
