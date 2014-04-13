#
# C utility library -- this is in straight C for greater accessibility
#
add_static_and_shared_library(adept_cutils link_utils.c)
use_c99_for_target(adept_cutils)
use_c99_for_target(adept_cutils_static)

install(TARGETS adept_cutils adept_cutils_static
        DESTINATION lib EXPORT adept_utils-libs)
install(FILES link_utils.h DESTINATION include)

add_executable(cutils-test test.c)
target_link_libraries(cutils-test adept_cutils dl)

include_directories(${PROJECT_BINARY_DIR})
