#ifndef __PY_STEPPYR_MODULES_H
#define __PY_STEPPYR_MODULES_H

namespace pybind11 {
    class module_;
}

void module_def_drivers(pybind11::module_ &m);
void module_def_stepdir(pybind11::module_ &m);
void module_def_profiles(pybind11::module_ &m);
void module_def_accel(pybind11::module_ &m);

#endif
