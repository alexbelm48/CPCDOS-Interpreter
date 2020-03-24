# Checks the CMake version
cmake_minimum_required(VERSION 3.14)

# Declares the project
project(
    CPCDOS-Interpreter
    DESCRIPTION         "CC+ interpreter written in C"
    LANGUAGES           C
    HOMEPAGE_URL        "https://github.com/0v3rl0w/CPCDOS-Interpreter"
)

# Sets the required C standard to gnu99/c99, depending on the support of the compiler
set(CMAKE_C_STANDARD 99)

# Appends required flags
string(APPEND CMAKE_C_FLAGS " --pedantic -Wall -Wextra -Wmissing-prototypes")

# Appends "-O0 -g" if in debug mode, or "-O3" if in release mode
if (CMAKE_BUILD_TYPE)
    string(APPEND CMAKE_C_FLAGS " -O0 -g")
else()
    string(APPEND CMAKE_C_FLAGS " -O3")
endif()

# Finds C source files in the "src" directory
file(GLOB_RECURSE CI_SOURCE_FILES "src/ci/*.c")

# Adds the include directory to the compiler's header path
include_directories("inc")

# Adds the executable target with the source files that we've found
add_executable(
    "cpc"
    ${CI_SOURCE_FILES}
)
