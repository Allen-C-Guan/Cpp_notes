//
// Created by Allen on 2021/4/24.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_THIRDPARTYDISPLAY_H
#define HEAD_FIRST_DESIGN_PARTTERN_THIRDPARTYDISPLAY_H
#include "Observer.h"
#include "Display.h"
#include "Subject.h"

// thirdpartyDisplay只关心其中的两个变量而不是全部
class ThirdPartyDisplay : public Observer , Display {
public:
    ThirdPartyDisplay(Subject *s) : s_(s) {
        s->registerObject(this);
    };
    void update(int temperature, int humidity, int pressure) override;
    void display() override;
private:
    Subject *s_;
    int humidity_;
    int pressure_;
};



#endif //HEAD_FIRST_DESIGN_PARTTERN_THIRDPARTYDISPLAY_H
