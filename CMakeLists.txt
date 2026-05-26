cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- ПРОСТОЕ ПОДКЛЮЧЕНИЕ GOOGLETEST ЧЕРЕЗ FETCHCONTENT ---
find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    message(STATUS "GTest не найден. Скачиваем через FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main # Используем ветку main, она всегда существует
    )
    FetchContent_MakeAvailable(googletest)
endif()

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
target_link_libraries(RunTests PRIVATE GTest::gmock_main MovingLogicLib pthread)

# --- АВТОМАТИЧЕСКИЙ ЗАПУСК ТЕСТОВ ---
include(GoogleTest)
gtest_discover_tests(RunTests)

# --- НАСТРОЙКА УПАКОВЩИКА CPACK ---
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "tests")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux")
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "tests shared library and tools")

# --- ИНСТРУКЦИИ ДЛЯ УСТАНОВКИ (INSTALL) ---
install(TARGETS MovingLogicLib DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
install(TARGETS RunTests DESTINATION bin)

include(CPack)
