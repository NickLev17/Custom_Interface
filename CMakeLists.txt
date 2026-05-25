cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_PREFIX_PATH /usr/share/cmake)

enable_testing()

find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
    message(STATUS "GTest не найден в системе. Будет скачан и собран из исходников.")
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.15.1.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()


add_library(MovingLogicLib
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_executable(RunTests tests/test_main.cpp)
target_include_directories(RunTests PRIVATE ${CMAKE_SOURCE_DIR}/include)


if(TARGET GTest::gmock AND TARGET GTest::gtest_main)
    target_link_libraries(RunTests PRIVATE
        GTest::gmock
        GTest::gtest
        GTest::gtest_main
        MovingLogicLib
        pthread
    )
elseif(TARGET gmock AND TARGET gtest_main)
    target_link_libraries(RunTests PRIVATE
        gmock
        gtest
        gtest_main
        MovingLogicLib
        pthread
    )
else()
    target_link_libraries(RunTests PRIVATE
        GTest::gmock
        GTest::gtest
        GTest::gtest_main
        MovingLogicLib
        pthread
    )
endif()

include(GoogleTest)
gtest_discover_tests(RunTests)
