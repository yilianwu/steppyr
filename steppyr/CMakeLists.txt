include_directories("include")

pybind11_add_module(py_steppyr MODULE
    src/steppyr.cpp
    src/drivers/drivers.cpp
    src/drivers/stepdir.cpp
    src/profiles/profiles.cpp
    src/profiles/accel.cpp
)
target_link_libraries(py_steppyr PRIVATE steppyr-static)
set_target_properties(py_steppyr PROPERTIES
    OUTPUT_NAME "steppyr"
)
