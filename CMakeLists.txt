cmake_minimum_required(VERSION 3.14)
project(ega10)

set(CMAKE_CXX_STANDARD 17)

add_executable(ega10 main.cpp progeny.cpp progeny.h procreator_choice.cpp crossover.cpp crossover.h procreator_choice.h mutation.h mutation.cpp selection.h selection.cpp stop_condition.h)