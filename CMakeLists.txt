cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject
    VERSION 1.0.0 
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- УМНОЕ ПОДКЛЮЧЕНИЕ GOOGLETEST ---
# Проверяем, существует ли папка external/googletest.
# Если ДА (в GitHub Actions), подключаем как поддиректорию.
# Если НЕТ (на локальном ПК), скачиваем через FetchContent.
if(EXISTS "${CMAKE_SOURCE_DIR}/external/googletest")
    message(STATUS "Папка external/googletest найдена. Использую add_subdirectory.")
    add_subdirectory(external/googletest)
else()
    message(STATUS "Папка external/googletest не найдена. Использую FetchContent для скачивания.")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        # Используем конкретный коммит, который точно существует
        GIT_TAG        609221a7e85a734037d28370346fa035c3295301 
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

# Используем версию проекта для имени файла (например, tests-1.0.0-Linux.deb)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "tests shared library and tools")


# --- ИНСТРУКЦИИ ДЛЯ УСТАНОВКИ (INSTALL) ---
install(TARGETS MovingLogicLib DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
install(TARGETS RunTests DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/tests/ DESTINATION tests FILES_MATCHING PATTERN "*.cpp")


include(CPack)
