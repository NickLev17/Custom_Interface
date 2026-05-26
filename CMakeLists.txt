cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    message(STATUS "GTest не найден в системе. Будет скачан и собран из исходников.")
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.15.1
    )

    # Для Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    # Отключаем сборку тестов внутри googletest (это часто вызывает ошибки в CI)
    set(BUILD_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)

    if(NOT TARGET GTest::gmock_main)
        add_library(GTest::gmock_main ALIAS gmock_main)
    endif()
endif()

add_library(MovingLogicLib
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(RunTests tests/test_main.cpp)

target_link_libraries(RunTests PRIVATE
    GTest::gmock_main
    MovingLogicLib
)

include(GoogleTest)
gtest_discover_tests(RunTests)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "tests")
set(CPACK_PACKAGE_FILE_NAME "tests-0.0.1-Linux")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 1)
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "tests shared library and tools")

include(CPack)
