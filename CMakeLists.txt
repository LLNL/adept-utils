###############################################################
# Adept Utilities
#
# This project is a set of libraries for commonly useful
# routines for ADEPT code projects.
###############################################################
project(adept-utils)
cmake_minimum_required(VERSION 2.8)

# Version information comes from here.  Incrememnt these when new stuff happens.
set(ADEPT_UTILS_MAJOR_VERSION 0)
set(ADEPT_UTILS_MINOR_VERSION 1)
set(ADEPT_UTILS_PATCH_VERSION 0)
set(ADEPT_UTILS_VERSION "${ADEPT_UTILS_MAJOR_VERSION}.${ADEPT_UTILS_MINOR_VERSION}.${ADEPT_UTILS_PATCH_VERSION}")

# Add our module directory to the include path.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(StaticAndShared)
include(C99Support)

# Muster requires boost for matrices and random number generators.
find_package(Boost NO_MODULE QUIET)
if(NOT Boost_FOUND)
  find_package(Boost)
endif()

# Check for various timing functions, so we can support highest-resolution timers available.
include(CheckFunctionExists)
include(CheckSymbolExists)

set(CMAKE_REQUIRED_INCLUDES  time.h sys/time.h)
set(CMAKE_REQUIRED_LIBRARIES rt)
check_function_exists(clock_gettime ADEPT_UTILS_HAVE_CLOCK_GETTIME)

set(CMAKE_REQUIRED_INCLUDES  sys/time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(gettimeofday ADEPT_UTILS_HAVE_GETTIMEOFDAY)

set(CMAKE_REQUIRED_INCLUDES  mach/mach.h mach/mach_time.h)
unset(CMAKE_REQUIRED_LIBRARIES)
check_function_exists(mach_absolute_time ADEPT_UTILS_HAVE_MACH_TIME)

check_symbol_exists(_r_debug link.h ADEPT_UTILS_HAVE_RDEBUG)

# Configure a header file with all the variables we found.
configure_file(
  ${PROJECT_SOURCE_DIR}/adept-utils-config.h.in
  ${PROJECT_BINARY_DIR}/adept-utils-config.h)
install(FILES ${PROJECT_BINARY_DIR}/adept-utils-config.h DESTINATION include)

# Configure a CMake file and set it to be installed.  This file tells other projects
# how to use Adept Utils.
configure_file(
  ${PROJECT_SOURCE_DIR}/adept_utils-config.cmake.in
  ${PROJECT_BINARY_DIR}/adept_utils-config.cmake
  @ONLY)

install(FILES ${PROJECT_BINARY_DIR}/adept_utils-config.cmake DESTINATION share/cmake/adept_utils)
install(EXPORT adept_utils-libs                              DESTINATION share/cmake/adept_utils)


# Configure subdirectories here, after everything else, so that they
# inherit variables set in the global scope.
add_subdirectory(timing)
if (ADEPT_UTILS_HAVE_RDEBUG)
  add_subdirectory(cutils)
endif()
add_subdirectory(utils)
add_subdirectory(test)

