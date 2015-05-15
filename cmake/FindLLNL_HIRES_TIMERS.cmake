include(FindPackageHandleStandardArgs)

# search for LLNL hires-timers
find_path(LLNL_HIRES_TIMERS_INCLUDE_DIR hires-timers.h)
find_library(LLNL_HIRES_TIMERS_LIBRARY hires-timers)

# process found items
find_package_handle_standard_args(LLNL_HIRES_TIMERS DEFAULT_MSG
	LLNL_HIRES_TIMERS_INCLUDE_DIR
	LLNL_HIRES_TIMERS_LIBRARY
)

# set variables for user
if (LLNL_HIRES_TIMERS_FOUND)
	set(LLNL_HIRES_TIMERS_INCLUDE_DIRS ${LLNL_HIRES_TIMERS_INCLUDE_DIR})
	set(LLNL_HIRES_TIMERS_LIBRARIES ${LLNL_HIRES_TIMERS_LIBRARY})
endif (LLNL_HIRES_TIMERS_FOUND)
