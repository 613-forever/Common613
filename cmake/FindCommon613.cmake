# - Try to find common613
#
# The following variables are optionally searched for defaults
#  Common613_ROOT_DIR
#
# The following are set after configuration is done: 
#  Common613_FOUND
#  Common613_INCLUDE_DIRS
#  Common613_LIBRARIES

include(FindPackageHandleStandardArgs)

find_package(fmt REQUIRED)
set(COMMON613_fmt_LIBRARIES fmt::fmt)

if (WIN32)
    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_LOG_DYN_LINK)
endif ()
find_package(Boost REQUIRED COMPONENTS log log_setup)
set(COMMON613_BOOST_LIBRARIES Boost::log Boost::log_setup Boost::boost)
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)
endif()

if (COMMON613_STACKTRACE_DEBUG)
#    if (WIN32)
        find_package(Boost COMPONENTS stacktrace_windbg)
        if (Boost_stacktrace_windbg_FOUND)
            add_definitions(-DCOMMON613_STACKTRACE_DEBUG=1)
            add_definitions(-DBOOST_STACKTRACE_USE_WINDBG)
            set(COMMON613_BOOST_LIBRARIES ${COMMON613_BOOST_LIBRARIES} Boost::stacktrace_windbg)
            if (MINGW)
                find_package(dbgeng REQUIRED)
                set(COMMON613_BOOST_LIBRARIES ${COMMON613_BOOST_LIBRARIES} ${dbgeng_LIBRARIES})
            endif(MINGW)
        else(Boost_stacktrace_windbg_FOUND)
            message("boost_stacktrace_windbg is not found, skip stacktrace")
        endif(Boost_stacktrace_windbg_FOUND)
#    else(WIN32)
#        find_package(Boost COMPONENTS stacktrace_basic)
#        if (Boost_stacktrace_basic_FOUND)
#            add_definitions(-DCOMMON613_STACKTRACE_DEBUG=1)
#            set(COMMON613_BOOST_LIBRARIES ${COMMON613_BOOST_LIBRARIES} Boost::stacktrace_basic)
#        else(Boost_stacktrace_basic_FOUND)
#            message("boost_stacktrace_basic is not found, skip stacktrace")
#        endif(Boost_stacktrace_basic_FOUND)
#    endif(WIN32)
endif(COMMON613_STACKTRACE_DEBUG)

find_path(Common613_INCLUDE_DIR
    NAMES
        common613/arith_utils.h
        common613/assertion.h
        common613/common.h
        common613/compat/cpp17.h
        common613/compat/file_system.h
        common613/file_utils.h
        common613/struct_size_check.h
    PATHS
        ${Common613_ROOT_DIR}/include/
    )

set(Common613_INCLUDE_DIRS ${Common613_INCLUDE_DIR})
set(Common613_LIBRARIES ${COMMON613_fmt_LIBRARIES} ${COMMON613_BOOST_LIBRARIES})

find_package_handle_standard_args(Common613 DEFAULT_MSG
    Common613_INCLUDE_DIR)
