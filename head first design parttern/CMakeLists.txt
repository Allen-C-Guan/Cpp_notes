cmake_minimum_required(VERSION 3.15)
project(head_first_design_parttern)

set(CMAKE_CXX_STANDARD 14)

add_executable(head_first_design_parttern main.cpp)
add_executable(strategy_parttern "strategy parttern/main_strategy_parttern.cpp" "strategy parttern/Duck.h" "strategy parttern/Duck.cpp" "strategy parttern/FlyBehavior.h" "strategy parttern/FlyBehavior.cpp" "strategy parttern/FlyRocketPowered.h" "strategy parttern/FlyWithWings.h" "strategy parttern/MallardDuck.h" "strategy parttern/ModelDuck.h" "strategy parttern/MuteQuack.h" "strategy parttern/Quack.h" "strategy parttern/QuackBehavior.h" "strategy parttern/RedHeadDuck.h" "strategy parttern/Squeak.h")
add_executable(observer_parttern "Observer Pattern/main Observer pattern.cpp" "Observer Pattern/Observer.h" "Observer Pattern/Display.h" "Observer Pattern/Subject.h" "Observer Pattern/CurrentConditionsDisplay.cpp" "Observer Pattern/CurrentConditionsDisplay.h" "Observer Pattern/WeatherData.h" "Observer Pattern/WeatherData.cpp" "Observer Pattern/ThirdPartyDisplay.h" "Observer Pattern/ThirdPartyDisplay.cpp")

add_executable(decorator_parttern "Decorator Pattern/decorator main.cpp" "Decorator Pattern/Beverage.h" "Decorator Pattern/drinks.cpp" "Decorator Pattern/drinks.h" "Decorator Pattern/decrator.cpp" "Decorator Pattern/decrator.h")
