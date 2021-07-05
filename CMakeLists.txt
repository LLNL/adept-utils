# This file is part of adept-utils.
#
# Copyright (C)
#   2010-2018 Lawrence Livermore National Laboratories, United States of America
#
# Written by Todd Gamblin, tgamblin@llnl.gov.
# LLNL-CODE-417602
#
# See the LICENSE file in the package base directory for details.

# minimum required CMake version
cmake_minimum_required(VERSION 2.8.12)


#
# project information
#
if (${CMAKE_MAJOR_VERSION} EQUAL 3)
	project("adept-utils" LANGUAGES C CXX)
else ()
	project("adept-utils" C CXX)
endif ()


# choose new behaviour for CMP0042
# see http://www.cmake.org/cmake/help/v3.0/policy/CMP0042.html for more details
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 NEW)
endif (POLICY CMP0042)


#
# cmake configuration
#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


#
# Version information comes from here. Incrememnt these when new stuff happens.
#
set(ADEPT_UTILS_MAJOR_VERSION 0)
set(ADEPT_UTILS_MINOR_VERSION 1)
set(ADEPT_UTILS_PATCH_VERSION 0)
set(ADEPT_UTILS_VERSION "${ADEPT_UTILS_MAJOR_VERSION}.${ADEPT_UTILS_MINOR_VERSION}.${ADEPT_UTILS_PATCH_VERSION}")


# Muster requires boost for matrices and random number generators.
find_package(Boost)

# Configure a CMake file and set it to be installed. This file tells other
# projects how to use Adept Utils.
configure_file(adept_utils-config.cmake.in adept_utils-config.cmake @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/adept_utils-config.cmake
	DESTINATION share/cmake/adept_utils
)
install(EXPORT adept_utils-libs DESTINATION share/cmake/adept_utils)


#
# recurse into subdirectories
#
add_subdirectory(cutils)
add_subdirectory(utils)
