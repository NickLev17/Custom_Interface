cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject VERSION 1.0)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск GTest в системе (например, если он установлен через apt или vcpkg)
find_package(GTest CONFIG QUIET)

# Если GTest не найден, скачиваем и собираем его из исходников
if(NOT GTest_FOUND)
    message(STATUS "GTest не найден в системе. Будет скачан и собран из исходников.")
    include(FetchContent)

    # Используем конкретную фиксацию (commit), которая соответствует стабильной версии,
    # вместо несуществующего тега release-1.15.1.
    # Этот коммит гарантированно существует.
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        609221a7e85a734037d28370346fa035c3295301 # Стабильный коммит
    )

    # Настройка для Windows (чтобы избежать проблем с библиотеками CRT)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()


# --- Сборка библиотеки с логикой ---
add_library(MovingLogicLib STATIC
    src/Point.cpp
    src/Commands/MoveCommand.cpp
)
target_include_directories(MovingLogicLib PUBLIC ${CMAKE_SOURCE_DIR}/include)


# --- Сборка тестового исполняемого файла ---
add_executable(RunTests tests/test_main.cpp)
target_include_directories(RunTests PRIVATE ${CMAKE_SOURCE_DIR}/include)


# --- Подключение библиотек к тестам ---
# Этот блок теперь не нужен, так как FetchContent_MakeAvailable создает цели GTest::gmock и GTest::gtest_main,
# если они доступны. Мы можем подключать их напрямую.
target_link_libraries(RunTests PRIVATE
    GTest::gmock_main   # Содержит main() и все необходимые компоненты для тестов
    MovingLogicLib      # Ваша библиотека с логикой
    pthread             # Требуется для работы потоков в gtest/gmock
)


# --- Автоматический запуск тестов ---
include(GoogleTest)
gtest_discover_tests(RunTests)
