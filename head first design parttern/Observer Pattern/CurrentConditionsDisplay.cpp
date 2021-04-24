#include <iostream>
#include "CurrentConditionsDisplay.h"

void CurrentConditionDisplay::update(int temperature, int humidity, int pressure) {
    temperature_ = temperature;
    humidity_ = humidity;
    pressure_ = pressure;
    std::cout << "CurrentConditionDisplay has been updated" << std::endl;
}

void CurrentConditionDisplay::display() {
    std::cout << "this is CurrentConditionDisplay" << std::endl;
    std::cout << "temperature = " << temperature_ << std::endl;
    std::cout << "humidity = " << humidity_ << std::endl;
    std::cout << "pressure = " << pressure_ << std::endl;
}