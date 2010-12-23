set(ADEPT_UTILS_SOURCES
  Timer.cpp
  matrix_utils.cpp)

set(ADEPT_UTILS_HEADERS
  Timer.h
  matrix_utils.h
  stl_utils.h)

add_library(adept-utils ${ADEPT_UTILS_SOURCES})
target_link_libraries(adept-utils timing)
install(TARGETS adept-utils DESTINATION lib)
install(FILES ${ADEPT_UTILS_HEADERS} DESTINATION include)

include_directories(
  ${Boost_INCLUDE_DIR}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/timing)
