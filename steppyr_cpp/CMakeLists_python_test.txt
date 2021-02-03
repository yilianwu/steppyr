add_library(python_modules INTERFACE)

target_include_directories(python_modules
    INTERFACE
        "${CMAKE_SOURCE_DIR}/include"
        Boost::python3
        Python3::Module
)

# Set up the libraries and header search paths for this target
target_link_libraries(python_modules
    INTERFACE
        Boost::python3
        Python3::Module
)


# Add a shared module - modules are intended to be imported at runtime.
# - This is where you add the source files
add_library(steppyr SHARED
    steppyr.cpp
)
target_include_directories(steppyr PRIVATE python_modules)
target_link_libraries(steppyr PRIVATE python_modules)
# Without this, any build libraries automatically have names "lib{x}.so"
set_target_properties(steppyr PROPERTIES
    OUTPUT_NAME "__init__"
    PREFIX ""
    CMAKE_CXX_STANDARD 11
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/steppyr"
)

add_library(drivers SHARED
    drivers/drivers.cpp
)
target_include_directories(drivers PRIVATE python_modules)
target_link_libraries(drivers PRIVATE python_modules)
# Without this, any build libraries automatically have names "lib{x}.so"
set_target_properties(drivers PROPERTIES
    OUTPUT_NAME "__init__"
    PREFIX ""
    CMAKE_CXX_STANDARD 11
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/steppyr/drivers"
)

