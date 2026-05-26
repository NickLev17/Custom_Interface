cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- ПОДКЛЮЧЕНИЕ GOOGLETEST ИЗ ПОДДИРЕКТОРИИ (SUBMODULE) ---
# CMake соберет GoogleTest из папки external/googletest,
# которая будет подготовлена GitHub Actions.
add_subdirectory(external/googletest)

enable_testing()

# --- СБОРКА БИБЛИОТЕКИ ---
add_library(MovingLogicLib STATIC
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# --- СБОРКА ТЕСТОВОГО ИСПОЛНЯЕМОГО ФАЙЛА ---
add_executable(RunTests tests/test_main.cpp)
target_include_directories(RunTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- ПОДКЛЮЧЕНИЕ БИБЛИОТЕК (ПРОСТОЙ И НАДЕЖНЫЙ СПОСОБ) ---
# GTest::gmock_main включает в себя все необходимое для запуска тестов.
target_link_libraries(RunTests PRIVATE
    GTest::gmock_main 
    MovingLogicLib
    pthread
)

# --- АВТОМАТИЧЕСКИЙ ЗАПУСК ТЕСТОВ ---
include(GoogleTest)
gtest_discover_tests(RunTests)

# --- НАСТРОЙКА УПАКОВЩИКА CPACK ---
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
