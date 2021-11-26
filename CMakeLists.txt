cmake_minimum_required(VERSION 3.20)
project(AiSD)

set(CMAKE_CXX_STANDARD 20)

if (${MSVC})
    MESSAGE("-- Build by MSVC")
elseif(${UNIX})
    MESSAGE(WARNING "-- Build in unix. May has some issues.")
else()
    MESSAGE(FATAL_ERROR "Unknown system")
endif ()

add_subdirectory(task1)
add_subdirectory(task2)
add_subdirectory(task3)
