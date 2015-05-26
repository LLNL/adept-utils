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


#
# include required modules
#
include(StaticAndShared)


#
# search for required modules
#
find_package(LLNL_HIRES_TIMERS REQUIRED)
find_package(Boost REQUIRED)


#
# Build Adept Utils library.
#
set(ADEPT_UTILS_SOURCES
	Timer.cpp
	io_utils.cpp
	string_utils.cpp
	matrix_utils.cpp
)

set(ADEPT_UTILS_HEADERS
	Timer.h
	io_utils.h
	two_utils.h
	string_utils.h
	matrix_utils.h
	mpi_utils.h
	stl_utils.h
)


# include directories for compiling
include_directories(
	${LLNL_HIRES_TIMERS_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

# build static and shared library
add_static_and_shared_library(adept_utils ${ADEPT_UTILS_SOURCES})

# link against LLNL hires-timers
target_link_libraries(adept_utils ${LLNL_HIRES_TIMERS_LIBRARIES})
target_link_libraries(adept_utils_static ${LLNL_HIRES_TIMERS_LIBRARIES})

# install
install(TARGETS adept_utils adept_utils_static
	DESTINATION lib
	EXPORT adept_utils-libs
)
install(FILES ${ADEPT_UTILS_HEADERS}
	DESTINATION include
)
