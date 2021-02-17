include_directories("include")
link_libraries(steppyr)

pybind11_add_module(py_steppyr MODULE
    src/steppyr.cpp
    src/drivers/drivers.cpp
    src/drivers/stepdir.cpp
    src/profiles/profiles.cpp
    src/profiles/accel.cpp
)
set_target_properties(py_steppyr PROPERTIES
    OUTPUT_NAME "steppyr"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/steppyr/"
)
