cmake_minimum_required(VERSION 3.15)
project(Effective_Cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(Effective_Cpp main.cpp)
add_executable(const "Const/const.cpp" "35. consider alternatives to virtual functions (strategy mode)/strategy mode and method template mode.h")
add_executable(singleton "Singleton/singleton.cpp")
add_executable(multiple_inheritance "multiple inheritance and virtual public/multiple inheritance.cpp")
add_executable(never_call_virtual_func_in_constructor_or_destructor "never call virtual func in constructor or destructor/prover.cpp")
add_executable(CopyConstructor "Copy Constructor/CopyConstructorTest.cpp")