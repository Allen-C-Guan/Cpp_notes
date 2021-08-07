//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_LIGHTONCMD_H
#define HEAD_FIRST_DESIGN_PARTTERN_LIGHTONCMD_H
#include "Light.h"
#include "Command.h"
#include <memory>
class LightOnCmd : public Command{
public:
    // 只要开灯就行了，不用管是什么等，是个灯就行
    LightOnCmd(std::shared_ptr<Light>& light):light_(light) {}
    ~LightOnCmd() = default;
    void execute() override
    {
        light_->on();
    }
    // lightOn的命令的撤销就是off
    void undo() override
    {
        light_->off();
    }
private:
    // onCmd和OffCmd有共享light的诉求，因此采用shard_ptr来实现
    std::shared_ptr<Light> light_;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_LIGHTONCMD_H
