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
include(CheckSymbolExists)
include(C99Support)
include(StaticAndShared)


# check for r_debug in link.h
check_symbol_exists(_r_debug link.h HAVE_RDEBUG)
if (HAVE_RDEBUG)
	#
	# build C utility library
	#
	add_static_and_shared_library(adept_cutils link_utils.c)

	# enable C99 support
	use_c99_for_target(adept_cutils)
	use_c99_for_target(adept_cutils_static)

	# install libraries
	install(TARGETS adept_cutils adept_cutils_static
		DESTINATION lib
		EXPORT adept_utils-libs
	)
	install(FILES link_utils.h DESTINATION include)

	# add test executable
	add_executable(cutils-test test.c)
	target_link_libraries(cutils-test adept_cutils dl)
endif(HAVE_RDEBUG)
