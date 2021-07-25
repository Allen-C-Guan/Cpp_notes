//
// Created by Allen on 2021/4/22.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_CURRENTCONDITIONSDISPLAY_H
#define HEAD_FIRST_DESIGN_PARTTERN_CURRENTCONDITIONSDISPLAY_H
#include "Observer.h"
#include "Display.h"
#include "Subject.h"
class CurrentConditionDisplay : public Observer, Display {
public:
    CurrentConditionDisplay(Subject *s) : subjectPtr(s) {
        s->registerObject(this);
    }
    void update (int temperature, int humidity, int pressure) override;
    void display() override;
    ~CurrentConditionDisplay()
    {
        std::cout << "current has been destroyed" << std::endl;
        subjectPtr->removeObject(this);
    }

private:
    Subject* subjectPtr;
    int temperature_;
    int humidity_;
    int pressure_;
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_CURRENTCONDITIONSDISPLAY_H
