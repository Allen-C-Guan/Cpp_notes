//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_COMMAND_H
#define HEAD_FIRST_DESIGN_PARTTERN_COMMAND_H


class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_COMMAND_H
