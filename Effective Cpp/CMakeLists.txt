cmake_minimum_required(VERSION 3.15)
project(Effective_Cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(Effective_Cpp main.cpp)
add_executable(const "Const/const.cpp")
add_executable(singleton "Singleton/singleton.cpp")
add_executable(multiple_inheritance "multiple inheritance and virtual public/multiple inheritance.cpp")
add_executable(never_call_virtual_func_in_constructor_or_destructor "never call virtual func in constructor or destructor/prover.cpp")