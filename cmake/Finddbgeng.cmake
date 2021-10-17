# - Try to find dbgeng
#
# The following variables are optionally searched for defaults
#  dbgeng_ROOT_DIR
#
# The following are set after configuration is done: 
#  dbgeng_FOUND
#  dbgeng_INCLUDE_DIRS
#  dbgeng_LIBRARIES

include(FindPackageHandleStandardArgs)

find_path(dbgeng_INCLUDE_DIR
    NAMES
        dbgeng.h
    PATHS
        ${dbgeng_ROOT_DIR}/include/
    )
set(dbgeng_LIBRARY "${dbgeng_ROOT_DIR}/lib/libdbgeng.a")

set(dbgeng_INCLUDE_DIRS ${dbgeng_INCLUDE_DIR})
set(dbgeng_LIBRARIES ${dbgeng_LIBRARY})

find_package_handle_standard_args(dbgeng DEFAULT_MSG
    dbgeng_INCLUDE_DIR dbgeng_LIBRARY)
