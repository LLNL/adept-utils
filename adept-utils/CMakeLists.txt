set(ADEPT_UTILS_SOURCES
  Timer.cpp
  io_utils.cpp
  matrix_utils.cpp
  string_utils.cpp)

set(ADEPT_UTILS_HEADERS
  Timer.h
  io_utils.h
  two_utils.h
  string_utils.h
  matrix_utils.h
  mpi_utils.h
  stl_utils.h)

add_library(adept-utils ${ADEPT_UTILS_SOURCES})
target_link_libraries(adept-utils adept-timing)
install(TARGETS adept-utils DESTINATION lib EXPORT adept-utils-libs)
install(FILES ${ADEPT_UTILS_HEADERS} DESTINATION include)

include_directories(
  ${Boost_INCLUDE_DIR}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/timing)
