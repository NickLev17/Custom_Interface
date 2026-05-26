cmake_minimum_required(VERSION 3.14) # Версия с поддержкой CPM или просто 3.11+
project(TestsProject)

# Устанавливаем стандарт C++ (рекомендуется)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ПОДКЛЮЧЕНИЕ GOOGLETEST ИЗ ПОДДИРЕКТОРИИ (SUBMODULE) ---
# Это самый надежный способ. CMake соберет GoogleTest из папки external/googletest.
add_subdirectory(external/googletest)

# --- СБОРКА ВАШЕЙ БИБЛИОТЕКИ ---
add_library(MovingLogicLib
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)

# Указываем путь к заголовочным файлам вашей библиотеки
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)


# --- СБОРКА ТЕСТОВОГО ИСПОЛНЯЕМОГО ФАЙЛА ---
add_executable(RunTests tests/test_main.cpp)

# Подключаем к тестам:
# 1. Вашу библиотеку с логикой.
# 2. gtest_main (содержит функцию main для запуска тестов).
# 3. gtest (содержит макросы ASSERT_EQ и т.д.).
target_link_libraries(RunTests PRIVATE MovingLogicLib gtest_main gtest)

# Указываем путь к заголовкам вашей библиотеки для тестового файла
target_include_directories(RunTests PRIVATE ${CMAKE_SOURCE_DIR}/include)


# --- АВТОМАТИЧЕСКИЙ ПОИСК И ЗАПУСК ТЕСТОВ ---
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
