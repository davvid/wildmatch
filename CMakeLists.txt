cmake_minimum_required(VERSION 2.6.0)
project(wildmatch)
include(GNUInstallDirs)

set(CMAKE_VERBOSE_MAKEFILE true)
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 5)
set(${PROJECT_NAME}_PATCH_LEVEL 0)
# Flags
set(CMAKE_CXX_FLAGS -fPIC)
add_definitions(-Wextra -Wno-unused-parameter)
include_directories(${CMAKE_SOURCE_DIR})

# Library
file(GLOB sources "*.cpp")
add_library(wildmatch SHARED ${sources})
install(TARGETS wildmatch DESTINATION ${CMAKE_INSTALL_LIBDIR})
