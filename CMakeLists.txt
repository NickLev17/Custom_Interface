
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


    if(NOT TARGET GTest::gmock_main)
        add_library(GTest::gmock_main ALIAS gmock_main)
    endif()
    if(NOT TARGET GTest::gmock)
        add_library(GTest::gmock ALIAS gmock)
    endif()
    if(NOT TARGET GTest::gtest_main)
        add_library(GTest::gtest_main ALIAS gtest_main)
    endif()
    if(NOT TARGET GTest::gtest)
        add_library(GTest::gtest ALIAS gtest)
    endif()
endif()

add_library(MovingLogicLib
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_executable(RunTests tests/test_main.cpp)
target_include_directories(RunTests PRIVATE ${CMAKE_SOURCE_DIR}/include)


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
