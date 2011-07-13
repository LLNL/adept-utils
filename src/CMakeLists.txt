#
# Timing library -- this is in straight C for greater accessibility
#
add_library(adept_timing timing.c)
install(TARGETS adept_timing DESTINATION lib EXPORT adept_utils-libs)
install(FILES timing.h DESTINATION include)

if (CMAKE_C_COMPILER_ID STREQUAL XL)
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-qlanglvl=extc99")
elseif(CMAKE_COMPILER_ID STREQUAL Intel)
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-std=c99")
else()
  set_target_properties(adept_timing PROPERTIES COMPILE_FLAGS "-std=gnu99")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL BlueGeneL)
  include_directories(/bgl/BlueLight/ppcfloor/bglsys/include)
endif()

#
# Adept Utils library is C++, this includes utils headers, etc.
# Requires boost, so only build if boost is available.
#
if (Boost_FOUND)
  set(ADEPT_UTILS_SOURCES
    Timer.cpp
    io_utils.cpp
    string_utils.cpp
    matrix_utils.cpp)
  
  set(ADEPT_UTILS_HEADERS
    Timer.h
    io_utils.h
    two_utils.h
    string_utils.h
    matrix_utils.h
    mpi_utils.h
    stl_utils.h)

  add_library(adept_utils ${ADEPT_UTILS_SOURCES})
  target_link_libraries(adept_utils adept_timing)
  install(TARGETS adept_utils DESTINATION lib EXPORT adept_utils-libs)
  install(FILES ${ADEPT_UTILS_HEADERS} DESTINATION include)
  
  include_directories(
    ${Boost_INCLUDE_DIR}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/timing)
endif()
