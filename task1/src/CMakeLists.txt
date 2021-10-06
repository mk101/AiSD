add_library(core TBitField.cpp TSet.cpp tests.cpp)
target_include_directories(core PUBLIC ../include)

add_executable(task1 main.cpp)
target_link_libraries(task1 core)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main core)