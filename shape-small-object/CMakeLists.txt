cmake_minimum_required (VERSION 3.0)
set(PROJECT_NAME_STR shapes)
project (${PROJECT_NAME_STR})

# Local project include directory
include_directories("${CMAKE_SOURCE_DIR}/include")

# Build binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

set(WARNFLAGS "-Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
list(APPEND CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libstdc++ ${WARNFLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
list(APPEND CMAKE_CXX_FLAGS "${WARNFLAGS}")
else()
message(FATAL_ERROR "Unsupported compiler")
endif()

#Process subdirectories
add_subdirectory(src)
add_subdirectory(app)
