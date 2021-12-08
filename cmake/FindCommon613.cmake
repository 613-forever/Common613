# - Try to find common613
#
# The following variables are optionally searched for defaults
#  Common613_ROOT_DIR
#
# The following are set after configuration is done: 
#  Common613_FOUND
#  Common613_INCLUDE_DIRS
#  Common613_LIBRARIES
#
# The following target is exported:
#  Common613::Common613

include(FindPackageHandleStandardArgs)
include(PrepareCommon613)

find_package_handle_standard_args(Common613 DEFAULT_MSG
    Common613_INCLUDE_DIR)

add_library(Common613 INTERFACE IMPORTED ${Common613_HEADERS})
target_include_directories(Common613 INTERFACE ${Common613_INCLUDE_DIRS})
target_link_libraries(Common613 INTERFACE ${Common613_LIBRARIES})
add_library(Common613::Common613 ALIAS Common613)
