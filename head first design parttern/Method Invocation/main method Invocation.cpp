//
// Created by Allen on 2021/8/4.
//
//#include <memory>
#include "LightOnCmd.h"
#include "LightOffCmd.h"
#include "BedRoomLight.h"
#include "WashRoomLight.h"
#include "RemoteController.h"
int main ()
{
    // 创建两个灯
    std::shared_ptr<Light> bedroomLight = std::make_shared<BedroomLight>();
    std::shared_ptr<Light> washroomLight = std::make_shared<WashRoomLight>();
    // 创建一个开灯和关灯的动作，动作绑定卧室的灯
    // 我们看，这里两个command共享了1个bedroomLight，因此这里不能用unique_ptr
    std::shared_ptr<Command> bedroomLightOnCmd = std::make_shared<LightOnCmd>(bedroomLight);
    std::shared_ptr<Command> bedroomLightOffCmd = std::make_shared<LightOffCmd>(bedroomLight);
    // 创建一个开灯和关灯的动作，动作绑定厕所的灯
    std::shared_ptr<Command> washroomLightOnCmd = std::make_shared<LightOnCmd>(washroomLight);
    std::shared_ptr<Command> washroomLightOffCmd = std::make_shared<LightOffCmd>(washroomLight);

    // 新建一个遥控器
    RemoteController remoteController;
    // 配置遥控器各个按键的功能
    remoteController.setCommand(0, bedroomLightOnCmd, bedroomLightOffCmd);
    remoteController.setCommand(1, washroomLightOnCmd, washroomLightOffCmd);
    // 使用遥控器
    remoteController.onButtonWasPushed(0);
    remoteController.onButtonWasPushed(1);
    remoteController.closeButtonWasPushed(0);
    remoteController.closeButtonWasPushed(1);
    // 使用其撤销功能
    remoteController.undo();


}