cmake_minimum_required(VERSION 3.28)
project(PendulumController LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ------------------------------------------------------------------------------
# SFML
# ------------------------------------------------------------------------------

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

# ------------------------------------------------------------------------------
# pybind11
# ------------------------------------------------------------------------------

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.13.6
)

FetchContent_MakeAvailable(pybind11)

# ------------------------------------------------------------------------------
# Simulation library
# ------------------------------------------------------------------------------

add_library(pendulum_lib
    src/simulation/pendulum.cpp
    src/simulation/double_pendulum.cpp
)

target_compile_features(pendulum_lib PUBLIC cxx_std_20)

target_include_directories(pendulum_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern
)

# ------------------------------------------------------------------------------
# Main executable
# ------------------------------------------------------------------------------

add_executable(main
    src/main.cpp
    src/rendering/pendulum_renderer.cpp
    src/rendering/double_pendulum_renderer.cpp
)

target_compile_features(main PRIVATE cxx_std_20)

target_link_libraries(main PRIVATE
    pendulum_lib
    SFML::Graphics
)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern
)

target_compile_definitions(main PUBLIC
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

# ------------------------------------------------------------------------------
# Python module
# ------------------------------------------------------------------------------

pybind11_add_module(pendulum_pysim
    src/bindings/pendulum_bindings.cpp
)

target_link_libraries(pendulum_pysim PRIVATE
    pendulum_lib
)

# ------------------------------------------------------------------------------
# Visual Studio
# ------------------------------------------------------------------------------



set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
