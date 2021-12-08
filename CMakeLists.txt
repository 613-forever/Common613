cmake_minimum_required(VERSION 3.10)
project(Common613
        VERSION 1.1.0
        DESCRIPTION "Common library for 613 repo"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(PrepareCommon613)

list(TRANSFORM Common613_HEADERS PREPEND "include/")

add_library(Common613 INTERFACE ${Common613_HEADERS})
target_include_directories(Common613 INTERFACE ${Common613_INCLUDE_DIRS})
target_link_libraries(Common613 INTERFACE ${Common613_LIBRARIES})
set_target_properties(Common613 PROPERTIES LINKER_LANGUAGE CXX)

export(TARGETS Common613 NAMESPACE Common613:: FILE ${PROJECT_NAME}Targets.cmake)

add_subdirectory(test)
