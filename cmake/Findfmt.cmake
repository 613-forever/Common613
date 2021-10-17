# - Try to find fmtlib
#
# The following variables are optionally searched for defaults
#  fmt_ROOT_DIR
#
# The following are set after configuration is done: 
#  fmt_FOUND
#  fmt_INCLUDE_DIRS
#  fmt_LIBRARIES

include(FindPackageHandleStandardArgs)

find_path(fmt_INCLUDE_DIR
    NAMES
        fmt/args.h
        fmt/color.h
        fmt/core.h
        fmt/format.h
        fmt/os.h
        fmt/printf.h
        fmt/xchar.h
        fmt/chrono.h
        fmt/compile.h
        fmt/format-inl.h
        fmt/locale.h
        fmt/ostream.h
        fmt/ranges.h
    PATHS
        ${fmt_ROOT_DIR}/include/
    )
if(MSVC)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(fmt_LIBRARY "${fmt_ROOT_DIR}/lib/fmtd.lib")
    else()
        set(fmt_LIBRARY "${fmt_ROOT_DIR}/lib/fmt.lib")
    endif()
else()
    set(fmt_LIBRARY "${fmt_ROOT_DIR}/lib/libfmt.a")
endif()

set(fmt_INCLUDE_DIRS ${fmt_INCLUDE_DIR})
set(fmt_LIBRARIES ${fmt_LIBRARY})

find_package_handle_standard_args(fmt DEFAULT_MSG
    fmt_INCLUDE_DIR fmt_LIBRARY)
