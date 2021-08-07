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
