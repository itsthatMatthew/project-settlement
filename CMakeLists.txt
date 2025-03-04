# Works with 3.15 and tested through 3.31
cmake_minimum_required(VERSION 3.15...3.31)

# Project name and a few useful settings. Other commands can pick up the results
project(
  "Project Settlement"
  VERSION 0.1.0
  DESCRIPTION "An isometric city building game"
  HOMEPAGE_URL "https://github.com/itsthatMatthew/project-settlement"
  LANGUAGES C CXX ASM
  )

# Optionally set things like CMAKE_CXX_STANDARD,
# CMAKE_POSITION_INDEPENDENT_CODE here
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

# This is needed for nvim clang intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Note this needs to be done in the main CMakeLists
# since it calls enable_testing, which must be in the
# main CMakeLists.
include(CTest)

# Use doxygen to generate the documentation
find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(docs)
else()
  message(STATUS "Doxygen not found, not building docs")
endif()

add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
)

if(SELECTED_OS STREQUAL "Linux")
    set(TEST_MSG "Chad")
else()
    set(TEST_MSG "Sojak")
endif()

# The code is here
add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

