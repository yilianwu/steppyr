# Add a shared module - modules are intended to be imported at runtime.
# - This is where you add the source files
add_library(steppyr SHARED
    src/steppyr.cpp
    src/drivers/drivers.cpp
    src/profiles/profiles.cpp
    src/profiles/accel.cpp
    src/utils.cpp
)

set_target_properties(steppyr PROPERTIES
    CXX_STANDARD 17
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/steppyr_cpp"
)
target_include_directories(steppyr
    PUBLIC
        "include"
    PRIVATE
        ${pigpio_INCLUDE_DIRS}
)
target_link_libraries(steppyr
    PRIVATE
        ${pigpio_LIBRARY}
)
