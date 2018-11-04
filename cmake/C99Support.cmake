# This file is part of adept-utils.
#
# Copyright (C)
#   2010-2018 Lawrence Livermore National Laboratories, United States of America
#
# Written by Todd Gamblin, tgamblin@llnl.gov.
# LLNL-CODE-417602
#
# See the LICENSE file in the package base directory for details.

function(use_c99_for_target target)
    # Force a C99 build.
    if (CMAKE_C_COMPILER_ID STREQUAL XL)
      set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-qlanglvl=extc99")
    elseif(CMAKE_COMPILER_ID STREQUAL Intel)
      set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-std=c99")
    else()
      set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-std=gnu99")
    endif()
endfunction()

