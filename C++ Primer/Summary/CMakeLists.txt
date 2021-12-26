cmake_minimum_required(VERSION 3.21)
project(Summary)

set(CMAKE_CXX_STANDARD 17)

add_executable(Summary main.cpp constructor.h destructor.h copy_and_move.h the_rules_of_three.h public_private_protected.h)
