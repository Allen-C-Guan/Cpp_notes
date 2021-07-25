#include <iostream>
#include <memory>
#include "CurrentConditionsDisplay.h"
#include "WeatherData.h"
#include "Subject.h"
#include "ThirdPartyDisplay.h"
int main () {
    std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();
    {
        std::shared_ptr<CurrentConditionDisplay> currConditionDisplay =
                std::make_shared<CurrentConditionDisplay>(weatherData.get());
        std::shared_ptr<ThirdPartyDisplay> thirdPartyDisplay =
                std::make_shared<ThirdPartyDisplay>(weatherData.get());
        weatherData->setMeasurementChanged(100, 40, 60);
        currConditionDisplay->display();
        thirdPartyDisplay->display();
        // thirdParty去订阅！
        weatherData->removeObject(thirdPartyDisplay.get());
        weatherData->setMeasurementChanged(10, 4, 6);
        currConditionDisplay->display();
        thirdPartyDisplay->display();
    }

}