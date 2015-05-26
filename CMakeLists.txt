# This file is part of adept-utils.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the disclaimer below.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the disclaimer (as noted below) in the
#   documentation and/or other materials provided with the distribution.
# * Neither the name of the LLNS/LLNL nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY, LLC, THE
# U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
# Additional BSD Notice:
#
# 1. This notice is required to be provided under our contract with the U.S.
#    Department of Energy (DOE). This work was produced at Lawrence Livermore
#    National Laboratory under Contract No. DE-AC52-07NA27344 with the DOE.
#
# 2. Neither the United States Government nor Lawrence Livermore National
#    Security, LLC nor any of their employees, makes any warranty, express or
#    implied, or assumes any liability or responsibility for the accuracy,
#    completeness, or usefulness of any information, apparatus, product, or
#    process disclosed, or represents that its use would not infringe
#    privately-owned rights.
#
# 3. Also, reference herein to any specific commercial products, process, or
#    services by trade name, trademark, manufacturer or otherwise does not
#    necessarily constitute or imply its endorsement, recommendation, or
#    favoring by the United States Government or Lawrence Livermore National
#    Security, LLC. The views and opinions of authors expressed herein do not
#    necessarily state or reflect those of the United States Government or
#    Lawrence Livermore National Security, LLC, and shall not be used for
#    advertising or product endorsement purposes.
#
#
# Copyright (c) 2010-2015, Lawrence Livermore National Security, LLC.
# Written by Todd Gamblin, tgamblin@llnl.gov.
# LLNL-CODE-417602
# All rights reserved.


project(adept-utils)
cmake_minimum_required(VERSION 2.8)


# choose new behaviour for CMP0042
# see http://www.cmake.org/cmake/help/v3.0/policy/CMP0042.html for more details
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 NEW)
endif (POLICY CMP0042)


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
include(CheckSymbolExists)

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
if (ADEPT_UTILS_HAVE_RDEBUG)
  add_subdirectory(cutils)
endif()
add_subdirectory(utils)
