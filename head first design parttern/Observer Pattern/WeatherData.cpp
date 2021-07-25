#include "WeatherData.h"
#include <algorithm>
#include <iostream>

void WeatherData::notifyObject () const
{
    for (auto o : observerList) {
        o->update(temperature_, humidity_, pressure_);
    }
}
void WeatherData::removeObject (Observer* o)
{
    auto ret = std::find(observerList.begin(), observerList.end(), o);
    if (ret != observerList.end()) {
        std::cout << "some observer has been removed" << std::endl;
        observerList.erase(ret);
    }

}
void WeatherData::registerObject (Observer* o) {
    observerList.push_back(o);
}

void WeatherData::setMeasurementChanged(int temperature, int humidity, int pressure) {
    temperature_ = temperature;
    humidity_ = humidity;
    pressure_ = pressure;
    meaturementChanged();
}

void WeatherData::meaturementChanged() {
    notifyObject();
}

int WeatherData::getPressure() {
    return 10;
}
int WeatherData::getHumidity() {
    return 98;
}
int WeatherData::getTemperature() {
    return 30;
}