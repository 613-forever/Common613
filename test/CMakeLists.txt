find_package(GTest REQUIRED)
include(GoogleTest)

set(${PROJECT_NAME}_TEST_SOURCES
        assert_test.cpp
        file_utils_test.cpp
        arith_utils_test.cpp
        vector_definitions_test.cpp
        vector_arith_utils_test.cpp
        )

add_executable(${PROJECT_NAME}_test
        EXCLUDE_FROM_ALL
        ${${PROJECT_NAME}_TEST_SOURCES}
        )
target_include_directories(${PROJECT_NAME}_test PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_test PUBLIC GTest::GTest GTest::Main ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME}_test)
