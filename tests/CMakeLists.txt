cmake_minimum_required(VERSION 3.14)
project(test_project)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ./test.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_FILE_HANDLER GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_DIR_HANDLER GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_SET GTest::gtest_main)
add_test(NAME first_test COMMAND ./${PROJECT_NAME})