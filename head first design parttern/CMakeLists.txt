cmake_minimum_required(VERSION 3.15)
project(head_first_design_parttern)

set(CMAKE_CXX_STANDARD 14)

add_executable(head_first_design_parttern main.cpp)
add_executable(strategy_parttern "strategy parttern/main_strategy_parttern.cpp" "strategy parttern/Duck.h" "strategy parttern/Duck.cpp" "strategy parttern/FlyBehavior.h" "strategy parttern/FlyBehavior.cpp" "strategy parttern/FlyRocketPowered.h" "strategy parttern/FlyWithWings.h" "strategy parttern/MallardDuck.h" "strategy parttern/ModelDuck.h" "strategy parttern/MuteQuack.h" "strategy parttern/Quack.h" "strategy parttern/QuackBehavior.h" "strategy parttern/RedHeadDuck.h" "strategy parttern/Squeak.h")
add_executable(observer_parttern "Observer Pattern/main Observer pattern.cpp" "Observer Pattern/Observer.h" "Observer Pattern/Display.h" "Observer Pattern/Subject.h" "Observer Pattern/CurrentConditionsDisplay.cpp" "Observer Pattern/CurrentConditionsDisplay.h" "Observer Pattern/WeatherData.h" "Observer Pattern/WeatherData.cpp" "Observer Pattern/ThirdPartyDisplay.h" "Observer Pattern/ThirdPartyDisplay.cpp")

add_executable(decorator_parttern "Decorator Pattern/decorator main.cpp" "Decorator Pattern/Beverage.h" "Decorator Pattern/drinks.cpp" "Decorator Pattern/drinks.h" "Decorator Pattern/decrator.cpp" "Decorator Pattern/decrator.h")
add_executable(factory_mode "Factory Mode/factory mode main.cpp" "Factory Mode/Pizza.cpp" "Factory Mode/Pizza.h" "Factory Mode/NYStyleCheesePizza.cpp" "Factory Mode/NYStyleCheesePizza.h" "Factory Mode/PizzaStore.cpp" "Factory Mode/PizzaStore.h" "Factory Mode/NYPizzaStore.cpp" "Factory Mode/NYPizzaStore.h" "Factory Mode/ChicagoStyleCheesePizza.cpp" "Factory Mode/ChicagoStyleCheesePizza.h" "Factory Mode/NYStylePepperoniPizza.cpp" "Factory Mode/NYStylePepperoniPizza.h" "Factory Mode/ChicagoPizzaStore.cpp" "Factory Mode/ChicagoPizzaStore.h" "Factory Mode/ChicagoStylePepperoniPizza.cpp" "Factory Mode/ChicagoStylePepperoniPizza.h" "Factory Mode/NYPizzaIngredientFactory.cpp" "Factory Mode/NYPizzaIngredientFactory.h" "Factory Mode/ChicagoPizzaIngredientFactory.cpp" "Factory Mode/ChicagoPizzaIngredientFactory.h")

add_executable(Method_Invocation "Method Invocation/main method Invocation.cpp" "Method Invocation/Command.h" "Method Invocation/Light.h" "Method Invocation/LightOnCmd.h" "Method Invocation/BedRoomLight.h" "Method Invocation/WashRoomLight.h" "Method Invocation/RemoteController.h" "Method Invocation/NoCommand.h" "Method Invocation/LightOffCmd.h")

add_executable(Adapter "Adapter/main Adapter.cpp" "Adapter/main Adapter.cpp")

add_executable(Encapsulation_Algorithm "Encapsulation Algorithm/main.cpp")
add_executable(StateMachine "StateMachine/main.cpp" StateMachine/state.h StateMachine/all_state.h StateMachine/all_state.cpp StateMachine/gumball_machine.h)