# Executable name can be variable
add_executable(main main.cpp)

# Optionally link any libraries that are needed by the binary

# Set up configure file to have access to CMake variables inside the code
configure_file( config.h.in ${CMAKE_BINARY_DIR}/generated/config.h )
# Make sure it can be included...
include_directories( ${CMAKE_BINARY_DIR}/generated/ )

