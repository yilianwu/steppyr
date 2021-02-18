#include <pybind11/pybind11.h>
#include <drivers/drivers.hpp>
#include <drivers/stepdir.hpp>
#include "modules.h"
namespace py = pybind11;

void module_def_stepdir(py::module_ &m)
{
    py::class_<StepDirDriver, Driver, std::shared_ptr<StepDirDriver>>(m, "StepDirDriver")
        .def(py::init<int, int>())
        .def(py::init<int, int, int>())
    ;
}
