# Add a shared module - modules are intended to be imported at runtime.
# - This is where you add the source files
set(steppyr_srcs
    src/steppyr.cpp
    src/drivers/drivers.cpp
    src/drivers/stepdir.cpp
    src/profiles/profiles.cpp
    src/profiles/accel.cpp
    src/utils.cpp
)

add_library(steppyr SHARED
    ${steppyr_srcs}
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


add_library(steppyr-static STATIC
    ${steppyr_srcs}
)
set_target_properties(steppyr-static PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
target_include_directories(steppyr-static
    PUBLIC
        "include"
    PRIVATE
        ${pigpio_INCLUDE_DIRS}
)
target_link_libraries(steppyr-static
    PRIVATE
        ${pigpio_LIBRARY}
)
