//
// Created by Allen on 2021/4/24.
//

#include "ThirdPartyDisplay.h"
#include "iostream"
void ThirdPartyDisplay::update(int temperature, int humidity, int pressure) {
    humidity_ = humidity;
    pressure_ = pressure;
    std::cout << "ThirdPartyDisplay has been updated" << std::endl;
}

void ThirdPartyDisplay::display() {
    std::cout << "ThirdPartyDisplay" << std::endl;
    std::cout << "humidity = " << humidity_ << "\npressure = " << pressure_ << std::endl;
}