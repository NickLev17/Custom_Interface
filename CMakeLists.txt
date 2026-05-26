cmake_minimum_required(VERSION 3.14)
project(MovingObjectProject
    VERSION 1.0.0 # Теперь версия берется отсюда
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- ПОДКЛЮЧЕНИЕ GOOGLETEST ИЗ ПОДДИРЕКТОРИИ (SUBMODULE) ---
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
target_link_libraries(RunTests PRIVATE GTest::gmock_main MovingLogicLib pthread)

# --- АВТОМАТИЧЕСКИЙ ЗАПУСК ТЕСТОВ ---
include(GoogleTest)
gtest_discover_tests(RunTests)

# --- НАСТРОЙКА УПАКОВЩИКА CPACK ---
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "tests")

# --- ГЛАВНОЕ ИЗМЕНЕНИЕ: Используем переменные проекта для имени файла ---
# Это автоматически создаст имя вроде tests-1.0.0-Linux.deb
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Убираем жестко заданное имя файла, чтобы CPack сам его сгенерировал
# set(CPACK_PACKAGE_FILE_NAME "tests-0.0.1-Linux") # УДАЛИТЕ ЭТУ СТРОКУ

set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "tests shared library and tools")


# --- ИНСТРУКЦИИ ДЛЯ УСТАНОВКИ (INSTALL) ---
install(TARGETS MovingLogicLib DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
install(TARGETS RunTests DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/tests/ DESTINATION tests FILES_MATCHING PATTERN "*.cpp")


include(CPack)
