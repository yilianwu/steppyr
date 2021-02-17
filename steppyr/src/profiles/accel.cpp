#include <pybind11/pybind11.h>
#include <profiles/profiles.hpp>
#include <profiles/accel.hpp>
#include "modules.h"
namespace py = pybind11;

void module_def_accel(pybind11::module_ &m)
{
    py::class_<AccelProfile, RampProfile>(m, "AccelProfile")
        .def(py::init<>())
    ;
}
