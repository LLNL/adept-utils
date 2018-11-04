# This file is part of adept-utils.
#
# Copyright (C)
#   2010-2018 Lawrence Livermore National Laboratories, United States of America
#
# Written by Todd Gamblin, tgamblin@llnl.gov.
# LLNL-CODE-417602
#
# See the LICENSE file in the package base directory for details.

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
