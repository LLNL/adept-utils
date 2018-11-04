# This file is part of adept-utils.
#
# Copyright (C)
#   2010-2018 Lawrence Livermore National Laboratories, United States of America
#
# Written by Todd Gamblin, tgamblin@llnl.gov.
# LLNL-CODE-417602
#
# See the LICENSE file in the package base directory for details.

function(add_static_and_shared_library target)
  get_property(supports_shared_libs GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)
  if (supports_shared_libs)
    add_library(${target} SHARED ${ARGN})
  endif()
  add_library(${target}_static STATIC ${ARGN})
  set_target_properties(${target}_static PROPERTIES OUTPUT_NAME ${target})
endfunction()
