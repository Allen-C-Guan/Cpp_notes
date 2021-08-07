//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_NOCOMMAND_H
#define HEAD_FIRST_DESIGN_PARTTERN_NOCOMMAND_H
#include "Command.h"
class NoCommand : public Command
{
public:
    NoCommand() = default;
    ~NoCommand() = default;
    // 啥也不做
    void execute() override
    {

    }
    // 啥也不做
    void undo () override
    {

    }

};
#endif //HEAD_FIRST_DESIGN_PARTTERN_NOCOMMAND_H
