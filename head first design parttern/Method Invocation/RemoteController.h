//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_REMOTECONTROLLER_H
#define HEAD_FIRST_DESIGN_PARTTERN_REMOTECONTROLLER_H

#include "NoCommand.h"
#include <memory>

constexpr int REMOTE_CONTROLLER_COMMANDS_SIZE = 6;
class RemoteController {
public:
    RemoteController()
    {
        for (auto& command : openCommands) {
            command = std::make_shared<NoCommand>();
        }
        lastCommand = std::make_shared<NoCommand>();
    }

    void setCommand(int slot, std::shared_ptr<Command>& openCommand, std::shared_ptr<Command>& closeCommand)
    {
        openCommands[slot] = openCommand;
        closeCommands[slot] = closeCommand;
    }

    void deleteCommand(int slot)
    {
        openCommands[slot] = std::make_shared<NoCommand>();
        closeCommands[slot] = std::make_shared<NoCommand>();
    }
    // 无论是开启，关闭，还是undo动作，command都致力于将自己变成莫得感情的调用机器，没有任何实际的工作内容
    // 所有的实际行为都在reciever内执行了， 用户调用cmd，cmd调用reicever来执行真正的动作。

    // 这样做的好处就在于cmd的通用性！而通用性的好处就在于用户和reciever之间，以及不同的reciever与reciever之间，
    // 均是解耦的！！！

    // 机制越傻瓜，则机制越通用，机制的通用性就要求其实际工作的对象的封装性要好，且严格按着机制来执行。
    void onButtonWasPushed(int slot)
    {
        openCommands[slot]->execute();
        lastCommand = openCommands[slot];
    }

    void closeButtonWasPushed(int slot)
    {
        closeCommands[slot]->execute();
        lastCommand = closeCommands[slot];
    }

    void undo()
    {
        lastCommand->undo();
    }

private:
    // 这里使用shared_ptr是因为command数组要和lastCommand共享command
    std::shared_ptr<Command> openCommands[REMOTE_CONTROLLER_COMMANDS_SIZE];
    std::shared_ptr<Command> closeCommands[REMOTE_CONTROLLER_COMMANDS_SIZE];
    std::shared_ptr<Command> lastCommand;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_REMOTECONTROLLER_H
