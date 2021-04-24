//
// Created by Allen on 2021/4/22.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_WEATHERDATA_H
#define HEAD_FIRST_DESIGN_PARTTERN_WEATHERDATA_H
#include "Subject.h"
#include <vector>

class WeatherData : public Subject {
public:
    void notifyObject () const override ;
    void removeObject (Observer* o) override ;
    void registerObject (Observer* o) override;
    void setMeasurementChanged(int temperature, int humidity, int pressure);
    int getPressure();
    int getHumidity();
    int getTemperature();
private:
    void meaturementChanged();
private:
    // 这些东西理应不是应该是一次性的，那么就应该用成员变量存下来，对于observer来说也是一样的
    int temperature_;
    int humidity_;
    int pressure_;

    std::vector<Observer*> observerList;

};

#endif //HEAD_FIRST_DESIGN_PARTTERN_WEATHERDATA_H
