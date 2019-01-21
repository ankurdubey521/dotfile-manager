cmake_minimum_required(VERSION 3.13)
project(dmgr)

set(CMAKE_CXX_STANDARD 14)

add_executable(dmgr main.cpp config.cpp config.h git_repo.cpp git_repo.h misc.cpp misc.h manager.cpp manager.h)
