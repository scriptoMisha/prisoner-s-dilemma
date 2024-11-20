cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(MyProject)

# Добавляем исходные файлы
set(SOURCES
tests.cpp
    
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov -fsanitize=address")

# Добавляем исполняемый файл

# Добавляем поддиректорию с библиотекой
add_subdirectory(lib)
add_executable(tests ${SOURCES})

# Связываем исполняемый файл с библиотекой
target_link_libraries(tests PRIVATE my_library gtest gtest_main)
target_compile_options(tests PRIVATE) 