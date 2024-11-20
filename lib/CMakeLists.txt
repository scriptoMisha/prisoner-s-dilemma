cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(MyLibrary)

# Добавляем исходные файлы
set(LIBRARY_SOURCES
    src/mode.cpp
    src/simulation.cpp
    src/strategy.cpp
)

# Добавляем исполняемый файл
add_library(my_library ${LIBRARY_SOURCES})

# Добавляем директорию include для поиска заголовочных файлов
target_include_directories(my_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(my_library PRIVATE gcov)
target_compile_options(my_library PRIVATE)



# Добавляем библиотеки (если есть)
# target_link_libraries(MyExecutable PRIVATE some_library)