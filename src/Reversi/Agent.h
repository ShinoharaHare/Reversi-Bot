#pragma once

#include <string>
#include "Board.h"

class Agent
{
public:
    Agent() = default;

    void set_name(const char *name);
    const char *get_name() const;

    virtual Position next_move(const Board &board, Color color) = 0;
    
protected:
    std::string _name;
};
