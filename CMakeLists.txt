cmake_minimum_required(VERSION 3.11)

project(YourProjectName)

# Включаем поддержку C++17 (или другой версии по необходимости)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Настройка GoogleTest ---
include(FetchContent)

# Объявляем зависимость от GoogleTest.
# Используем тег release-1.12.1, который точно существует.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

# Загружаем и собираем GoogleTest автоматически.
FetchContent_MakeAvailable(googletest)

# --- Настройка вашего проекта ---
# Добавляем исполняемый файл (пример)
add_executable(
  main
  src/main.cpp
)

# Добавляем тестовый файл (пример)
add_executable(
  my_test
  test/my_test.cpp
)

# Подключаем GoogleTest к тестовому файлу
target_link_libraries(
  my_test
  GTest::Main
  GTest::GTest
)
