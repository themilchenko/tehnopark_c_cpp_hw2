cmake_minimum_required(VERSION 3.18)

project("HW2" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_definitions(DEBUG)

option(SANITIZERS "Turn on sanitizers" OFF)

set(${PROJECT_NAME}_FILE_HANDLER_H ${CMAKE_SOURCE_DIR}/include/file_handler.h)
set(${PROJECT_NAME}_FILE_HANDLER_C ${CMAKE_SOURCE_DIR}/source/file_handler.c)
set(${PROJECT_NAME}_DIR_HANDLER_H ${CMAKE_SOURCE_DIR}/include/dir_handler.h)
set(${PROJECT_NAME}_DIR_HANDLER_C ${CMAKE_SOURCE_DIR}/source/dir_handler.c)
set(${PROJECT_NAME}_SET_H ${CMAKE_SOURCE_DIR}/include/set.h)
set(${PROJECT_NAME}_SET_C ${CMAKE_SOURCE_DIR}/source/set.c)
#set(${PROJECT_NAME}_PROCESS_HANDLER_H ${CMAKE_SOURCE_DIR}/include/process_handler.h)
#set(${PROJECT_NAME}_PROCESS_HANDLER_C ${CMAKE_SOURCE_DIR}/source/process_handler.c)
set(${PROJECT_NAME}_MAIN_C ${CMAKE_SOURCE_DIR}/source/main.c)

set(GCC_WARNINGS
        -Wmisleading-indentation
        -Wall
        -Wextra
        -Wshadow
        -Wcast-align
        -Wunused
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Werror
        -g
        -O0
        -Wno-error
        )
add_compile_options(${GCC_WARNINGS})

add_compile_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
add_link_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)

if (SANITIZERS)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif()

add_executable(${PROJECT_NAME} source/main.c)
add_library(${PROJECT_NAME}_FILE_HANDLER ${${PROJECT_NAME}_FILE_HANDLER_C})
add_library(${PROJECT_NAME}_DIR_HANDLER ${${PROJECT_NAME}_DIR_HANDLER_C})
add_library(${PROJECT_NAME}_SET ${${PROJECT_NAME}_SET_C})
#add_library(${PROJECT_NAME}_PROCESS_HANDLER ${${PROJECT_NAME}_PROCESS_HANDLER_C})

target_compile_options(${PROJECT_NAME}_FILE_HANDLER PUBLIC -fprofile-arcs -ftest-coverage -O0)
target_link_options(${PROJECT_NAME}_FILE_HANDLER PUBLIC -fprofile-arcs -ftest-coverage)

target_compile_options(${PROJECT_NAME}_DIR_HANDLER PUBLIC -fprofile-arcs -ftest-coverage -O0)
target_link_options(${PROJECT_NAME}_DIR_HANDLER PUBLIC -fprofile-arcs -ftest-coverage)

target_compile_options(${PROJECT_NAME}_SET PUBLIC -fprofile-arcs -ftest-coverage -O0)
target_link_options(${PROJECT_NAME}_SET PUBLIC -fprofile-arcs -ftest-coverage)

#target_compile_options(${PROJECT_NAME}_PROCESS_HANDLER PUBLIC -fprofile-arcs -ftest-coverage -O0)
#target_link_options(${PROJECT_NAME}_PROCESS_HANDLER PUBLIC -fprofile-arcs -ftest-coverage)

IF (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF ()

target_link_libraries(${PROJECT_NAME}_SET PRIVATE ${PROJECT_NAME}_FILE_HANDLER)
#target_link_libraries(${PROJECT_NAME}_PROCESS_HANDLER PUBLIC ${PROJECT_NAME}_FILE_HANDLER ${PROJECT_NAME}_DIR_HANDLER)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_FILE_HANDLER)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_DIR_HANDLER)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_SET)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_PROCESS_HANDLER)

include_directories(${CMAKE_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)
