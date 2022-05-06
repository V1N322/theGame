# CMakeList.txt: проект CMake для theGame; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (game "main.cpp" "theGame.h" "coordinates.h"    "Map.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
