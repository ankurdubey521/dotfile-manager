cmake_minimum_required(VERSION 3.13)
project(dotfile_manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(dotfile_manager main.cpp config.cpp config.h git_repo.cpp git_repo.h misc.cpp misc.h manager.cpp manager.h)