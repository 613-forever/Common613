cmake_minimum_required(VERSION 3.10)
project(Common613
        VERSION 1.0.0
        DESCRIPTION "Common library for 613 repo"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Boost REQUIRED COMPONENTS log log_setup filesystem)

find_package(fmt REQUIRED)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX -DBOOST_STACKTRACE_USE_WINDBG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler=\"${CMAKE_CXX_FLAGS}\"")
endif (MSVC)

find_package(GTest REQUIRED)
include(GoogleTest)

include_directories("./include")

add_library(${PROJECT_NAME} INTERFACE)
target_compile_definitions(${PROJECT_NAME} INTERFACE -DBOOST_LOG_DYN_LINK)
target_include_directories(${PROJECT_NAME} INTERFACE .)
target_include_directories(${PROJECT_NAME} INTERFACE
        ${Boost_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} INTERFACE
        Boost::log Boost::log_setup
        Boost::filesystem
        fmt::fmt
)
if (COMMON613_STACKTRACE_DEBUG)
#    if (WIN32)
        find_package(Boost COMPONENTS stacktrace_windbg)
        if (Boost_stacktrace_windbg_FOUND)
            add_definitions(-DCOMMON613_STACKTRACE_DEBUG=1)
            add_definitions(-DBOOST_STACKTRACE_USE_WINDBG)
            target_link_libraries(${PROJECT_NAME} INTERFACE Boost::stacktrace_windbg)
            if (MINGW)
                find_package(dbgeng REQUIRED)
                target_link_libraries(${PROJECT_NAME} INTERFACE ${dbgeng_LIBRARIES})
            endif(MINGW)
        else(Boost_stacktrace_windbg_FOUND)
            message("boost_stacktrace_windbg is not found, skip stacktrace")
        endif(Boost_stacktrace_windbg_FOUND)
#    else(WIN32)
#        find_package(Boost COMPONENTS stacktrace_basic)
#        if (Boost_stacktrace_basic_FOUND)
#            add_definitions(-DCOMMON613_STACKTRACE_DEBUG=1)
#            target_link_libraries(${PROJECT_NAME} INTERFACE Boost::stacktrace_basic)
#        else(Boost_stacktrace_basic_FOUND)
#            message("boost_stacktrace_basic is not found, skip stacktrace")
#        endif(Boost_stacktrace_basic_FOUND)
#    endif(WIN32)
endif(COMMON613_STACKTRACE_DEBUG)

add_executable(${PROJECT_NAME}_test
        test/assert_test.cpp test/file_utils_test.cpp test/arith_utils_test.cpp
        include/common613/compat/cpp17.h include/common613/compat/file_system.h
        include/common613/assert.h include/common613/file_utils.h
        include/common613/memory.h include/common613/struct_size_check.h
        include/common613/arith_utils.h)
target_include_directories(${PROJECT_NAME}_test PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_test PUBLIC GTest::GTest GTest::Main ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME}_test)
