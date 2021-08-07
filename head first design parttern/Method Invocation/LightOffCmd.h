//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_LIGHTOFFCMD_H
#define HEAD_FIRST_DESIGN_PARTTERN_LIGHTOFFCMD_H
#include "Light.h"
#include "Command.h"

class LightOffCmd : public Command {
public:
    LightOffCmd(std::shared_ptr<Light> &light) : light_(light) {}
    ~LightOffCmd() = default;
    void execute () override
    {
        light_->off();
    }

    void undo() override
    {
        light_->on();
    }
private:
   std::shared_ptr<Light> light_;
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_LIGHTOFFCMD_H
