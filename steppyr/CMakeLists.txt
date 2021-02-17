link_libraries(steppyr)

pybind11_add_module(py_steppyr MODULE src/steppyr.cpp)
set_target_properties(py_steppyr PROPERTIES
    OUTPUT_NAME "__init__"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/steppyr/"
)
